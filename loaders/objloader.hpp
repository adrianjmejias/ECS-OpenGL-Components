#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
//#include <future>

#include "../assets/Material.hpp"
#include "../assets/Mesh.hpp"
//#include "../assets/Texture.hpp"
//
//struct ObjectGroup{
//	
//};


//#define DEBUG_OBJ_LOADER
#ifdef DEBUG_OBJ_LOADER
#define DEBUG_PRINT(x) (x)
#else
#define DEBUG_PRINT(x) 
#endif // DEBUG


static std::vector<Material*> readMTLLIB(std::string folderPath, std::string nameMaterial);
static Material* readMaterial(std::ifstream &file, std::string nameMaterial);
static Mesh* readO(std::ifstream&, std::string, std::string, std::vector<Vec3_t>&, std::unordered_map<std::string, std::shared_ptr<Material>>&);


//http://paulbourke.net/dataformats/obj/
std::vector<Mesh*> loadObj(const std::string path)
{
	std::ifstream file(path, std::ios::in);
	std::string buffer;

	if (!file.is_open())
	{
		DEBUG_PRINT(std::cout << "Couldn't open file" << path << std::endl);
		__debugbreak();
		std::cin.ignore();
		exit(-1);
	}

	std::vector<Vec3_t> vertexData;
	std::vector<Mesh*> meshes;
	std::unordered_map<std::string, std::shared_ptr<Material>> materials;


	while (!file.eof() && file.good())
	{
		std::getline(file, buffer);
		std::stringstream stream(buffer);
		DEBUG_PRINT(std::cout << buffer << std::endl);
		{
			std::string tofData;
			stream >> tofData;

			if (tofData[0] == '#')
			{
				continue;
			}

			if (tofData == "o") {
				stream >> tofData;
				Mesh * m = readO(file, tofData, path, vertexData, materials);
				meshes.push_back(m);

				std::cout << m->name << std::endl;

			}
			else if (tofData == "mtllib") {
				std::cout << buffer << std::endl;

				stream >> tofData;
				std::string matPath = path.substr(0, path.find_last_of("/"));
				matPath.append("/" + tofData);

				std::vector<Material*> mats = readMTLLIB(matPath, buffer);
				for (auto mat : mats) {
					materials[mat->name].reset(mat);
				}
			}
			else if (tofData == "s")
			{
				stream >> buffer;

				// if
			}
		}
		DEBUG_PRINT(std::cout << "--------------------------" << std::endl);
		DEBUG_PRINT(std::cout << "--------------------------" << std::endl);
	}


	








	for (auto mesh : meshes)
	{

		mesh->face.pop_back();
	}

	for (auto mesh : meshes)
	{

		size_t numVertex = mesh->face.size();

		std::vector<std::vector<index_t>*> arrs({ &mesh->face, &mesh->faceNorm, &mesh->faceTex });
		std::vector<std::vector<Vec3_t>*> arrsTarg({ &mesh->vertex, &mesh->vertexNormal, &mesh->uv });
		std::vector<Vec3_t> aux;

		for (unsigned int ii = 0; ii < arrs.size(); ii++) {
			auto &arr = *arrs[ii];
			auto &arrTarget = *arrsTarg[ii];

			for (auto &f : arr) {
				//std::cout << f.x << " " << f.y << " " << f.z << std::endl;

				for (int ii = 0; ii < 3; ii++) {
					glm::u32& index = f[ii];
					if (index > 0) {
						index--;
					}
					else {
						index = (unsigned int)(numVertex + index);
					}


				}
				aux.push_back(arrTarget[f[0]]);
				aux.push_back(arrTarget[f[1]]);
				aux.push_back(arrTarget[f[2]]);

			}
			arrTarget = std::move(aux);
			

		}


	}


	return meshes;
}



static Mesh* readO(std::ifstream &file, std::string name, std::string path, std::vector<Vec3_t> &vertexData, std::unordered_map<std::string, std::shared_ptr<Material>>& materials) {
	Mesh *mesh(new Mesh());
	mesh->path = path;
	mesh->name = name;
	Vec3_t v;
	Vec2_t vt;
	Vec3_t vn;

	index_t f;
	index_t ft;
	index_t fn;
	std::string tofData;


	while (!file.eof() && file.good() && file.peek() != 'o')
	{
		std::string buffer;
		std::getline(file, buffer);
		std::stringstream stream(buffer);

		stream >> tofData;


		if (tofData == "v")
		{
			// while(!stream.eof()) //por ahora no triangula
			{
				stream >> v[0] >> v[1] >> v[2];

				mesh->vertex.push_back(v);
				vertexData.push_back(v);
				DEBUG_PRINT(std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl);
			}
		}
		else if (tofData == "vn")
		{
			mesh->hasNormals = true;

			// while(!stream.eof()) // por ahora no triangula
			{
				stream >> vn[0] >> vn[1] >> vn[2];
				mesh->vertexNormal.push_back(vn);
				vertexData.push_back(vn);
				DEBUG_PRINT(std::cout << "(" << vn[0] << ", " << vn[1] << ", " << vn[2] << ")" << std::endl);

			}
		}
		else if (tofData == "vt")
		{
			mesh->hasUVs = true;
			// while(!stream.eof()) // por ahora no triangula
			{
				stream >> vt[0] >> vt[1];

				mesh->uv.push_back(Vec3_t(vt[0], vt[1], 0.f));
				vertexData.push_back(Vec3_t(vt[0], vt[1], 0.f));
				DEBUG_PRINT(std::cout << "(" << vt[0] << ", " << vt[1] << ")" << std::endl);
			}
		}
		else if (tofData == "f")
		{
			auto posInit = stream.tellg();
			stream >> buffer;
			stream.seekg(posInit); // hago como si no hubiera leido nada del stream

			//x case f v1 v2 v3 ....
			//x case f v1/vt1 v2/vt2 v3/vt3 ...
			// case f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			// case f v1//vn1 v2//vn2 v3//vn3 ...

			bool hasDoubleSlash = false;
			unsigned int countDeSlash = 0;
			{
				unsigned int slashPos = buffer.find_first_of("/");
				hasDoubleSlash = (buffer[slashPos + 1]) == '/';
			}
			countDeSlash = std::count(buffer.begin(), buffer.end(), '/');

			DEBUG_PRINT(std::cout << hasDoubleSlash << " " << countDeSlash << std::endl);

			//std::vector<std::string> tokens;




			switch (countDeSlash)
			{
			case 0: // solo caras
			{

				stream >> f[0] >> f[1] >> f[2];

				mesh->face.push_back(f);
				DEBUG_PRINT(std::cout << "(" << f[0] << ", " << f[1] << ", " << f[2] << ")" << std::endl);
			}
			break;
			case 1: // caras y texturas
			{
				for (int ii = 0; ii < 3; ii++)
				{
					stream >> buffer;
					sscanf_s(buffer.c_str(), "%d/%d", &f[ii], &ft[ii]);

					DEBUG_PRINT(std::cout << "(" << f[ii] << ", " << ft[ii] << ")" << std::endl);
				}

				mesh->face.push_back(f);
				mesh->faceTex.push_back(ft);
			}
			break;
			case 2:
			{
				if (hasDoubleSlash)
				{ // caras y normales

					for (int ii = 0; ii < 3; ii++)
					{
						stream >> buffer;
						sscanf_s(buffer.c_str(), "%d//%d", &f[ii], &fn[ii]);
						DEBUG_PRINT(std::cout << "(" << f[ii] << ", " << fn[ii] << ")" << std::endl);
					}

					mesh->face.push_back(f);
					mesh->faceNorm.push_back(fn);

				}
				else
				{ //caras texturas y normales
					for (int ii = 0; ii < 3; ii++)
					{
						stream >> buffer;
						sscanf_s(buffer.c_str(), "%d/%d/%d", &f[ii], &ft[ii], &fn[ii]);
						DEBUG_PRINT(std::cout << "(" << f[ii] << ", " << ft[ii] << ", " << fn[ii] << ")" << std::endl);
					}

					mesh->face.push_back(f);
					mesh->faceNorm.push_back(fn);
					mesh->faceTex.push_back(ft);
				}
			}

			break;
			}
		}
		else if (tofData == "usemtl")
		{
			stream >> buffer;// pongo el nombre del material
			mesh->materials.push_back(materials[buffer]);
		}
	}

	return mesh;
}



//http://paulbourke.net/dataformats/mtl/
std::vector<Material*> readMTLLIB(std::string matPath, std::string nameMaterial) {

	std::vector<Material*> materials;
	std::ifstream file(matPath, std::ios::in);

	if (!file.is_open())
	{
		DEBUG_PRINT(std::cout << "Couldn't open material file" << matPath << std::endl);
		__debugbreak();

		return materials;
	}

	std::string buffer;
	while (!file.eof() && file.good())
	{
		std::string tofData;
		std::getline(file, buffer);

		std::stringstream stream(buffer);

		stream >> tofData;
		DEBUG_PRINT(std::cout << buffer << std::endl);
		{
			if (tofData == "newmtl") {
				std::cout << buffer << std::endl;
				stream >> tofData;

				materials.push_back(readMaterial(file, tofData));
			}
		}
	}
	DEBUG_PRINT(std::cout << "--------------------------" << std::endl);
	DEBUG_PRINT(std::cout << "--------------------------" << std::endl);

	return materials;
}


static Material* readMaterial(std::ifstream &file, std::string nameMaterial) {
	Material *material(new Material());
	material->name = nameMaterial;

	std::string buffer;
	while (!file.eof() && file.good())
	{
		std::string tofData;

		if (file.peek() == 'n') {
			return material;
		}

		std::getline(file, buffer);

		std::stringstream stream(buffer);

		stream >> tofData;
		DEBUG_PRINT(std::cout << buffer << std::endl);
		{


			// para los K falta espectral y xyz
			if (tofData == "Ka") {
				stream >> material->color[0];
				stream >> material->color[1];
				stream >> material->color[2];


			}
			else if (tofData == "Kd") {
				stream >> material->diffuse[0];
				stream >> material->diffuse[1];
				stream >> material->diffuse[2];
			}
			else if (tofData == "Ks") {
				stream >> material->specular[0];
				stream >> material->specular[1];
				stream >> material->specular[2];
			}
			else if (tofData == "Ns") {
				stream >> material->shiny;
			}
			else if (tofData == "Ni") {
				stream >> material->refractionIndex;
			}
			else if (tofData == "d") {
				stream >> material->dissolve;
			}
			else if (tofData == "bump") {

			}
			else if (tofData == "Tf") {

			}
			else if (tofData == "illum") {
				int type;
				stream >> type;

				//switch (type)
				//{
				//	//del 0 al 10 creo XD
				//default:
				//	break;
				//}
			}
		}
	}

	return material;
}




//void readRFL(); // esto es para el espectral de los K