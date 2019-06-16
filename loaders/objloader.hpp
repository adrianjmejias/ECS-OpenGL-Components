#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "../assets/Mesh.hpp"

std::shared_ptr<Mesh> loadObj(const std::string path, bool debug)
{
    std::ifstream file(path, std::ios::in);
    std::string buffer;
    Vec3_t v;
    Vec2_t vt;
    Vec3_t vn;

    index_t f;
    index_t ft;
    index_t fn;

    if (!file.is_open())
    {
        if(debug) std::cout << "Couldn't open file" << std::endl;
        exit(-1);
    }

    std::shared_ptr<Mesh> mesh(std::make_shared<Mesh>());

    while (!file.eof() && file.good())
    {
        std::getline(file, buffer);
        std::stringstream stream(buffer);
        if(debug) std::cout << buffer << std::endl;
        {
            std::string tofData;
            stream >> tofData;

            if (tofData[0] == '#')
            {
                continue;
            }

            if (tofData == "v")
            {
                // while(!stream.eof()) //por ahora no triangula
                {
                    stream >> v[0] >> v[1] >> v[2];
                    mesh->vertex.push_back(v);
                    if(debug) std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
                }
            }
            else if (tofData == "vn")
            {
                // while(!stream.eof()) // por ahora no triangula
                {
                    stream >> vn[0] >> vn[1] >> vn[2];
                    mesh->normal.push_back(vn);
                    if(debug) std::cout << "(" << vn[0] << ", " << vn[1] << ", " << vn[2] << ")" << std::endl;
                }
            }
            else if (tofData == "vt")
            {
                // while(!stream.eof()) // por ahora no triangula
                {
                    stream >> vt[0] >> vt[1];
                    mesh->uv.push_back(vt);
                    if(debug) std::cout << "(" << vt[0] << ", " << vt[1] << ")" << std::endl;
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
                int countDeSlash = 0;
                {
                    int slashPos = buffer.find_first_of("/");
                    hasDoubleSlash = (buffer[slashPos+1]) == '/';
                }
                countDeSlash = std::count(buffer.begin(), buffer.end(), '/');
                
                if(debug) std::cout << hasDoubleSlash <<" "<< countDeSlash << std::endl;
                
                switch (countDeSlash)
                {
                case 0: // solo caras
                {
                    for (int ii = 0; ii<3; ii++)
                    {
                        stream >> f[ii];
                    }

                    mesh->face.push_back(f);

                    if(debug) std::cout << "(" << f[0] << ", " << f[1] << ", " << f[2] << ")" << std::endl;
                }
                break;
                case 1: // caras y texturas
                {
                    for (int ii = 0; ii < 3; ii++)
                    {
                        stream >> buffer;
                        sscanf(buffer.c_str(), "%d/%d", &f[ii], &ft[ii]);

                        if(debug) std::cout << "(" << f[ii] << ", " << ft[ii] << ")" << std::endl;
                    }
                    mesh->face.push_back(f);
                    mesh->faceNorm.push_back(ft);
                }
                break;
                case 2:
                {
                    if (hasDoubleSlash)
                    { // caras y normales

                        for (int ii = 0; ii < 3; ii++)
                        {
                            stream >> buffer;
                            sscanf(buffer.c_str(), "%d//%d", &f[ii], &fn[ii]);
                            if(debug) std::cout << "(" << f[ii] << ", " << fn[ii] << ")" << std::endl;
                        }
                        mesh->face.push_back(f);
                        mesh->faceNorm.push_back(fn);
                    }
                    else
                    { //caras texturas y normales
                        for (int ii = 0; ii < 3; ii++)
                        {
                            stream >> buffer;
                            sscanf(buffer.c_str(), "%d/%d/%d", &f[ii], &ft[ii], &fn[ii]);
                            if(debug) std::cout<< "hola";
                            if(debug) std::cout << "(" << f[ii] << ", " << ft[ii] << ", " << fn[ii] << ")" << std::endl;
                        }
                        mesh->face.push_back(f);
                        mesh->faceTex.push_back(ft);
                        mesh->faceNorm.push_back(fn);
                    }
                }

                break;
                }
            }
            else if (tofData == "usemtl")
            {
                stream >> buffer;
            }
            else if (tofData == "s")
            {
                stream >> buffer;

                // if
            }
        }
        if(debug) std::cout << "--------------------------" << std::endl;
        if(debug) std::cout << "--------------------------" << std::endl;
    }

    return mesh;
}
