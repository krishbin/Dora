#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char, const std::string, bool gamma=false);

class Model 
{
  public:
    vector<Texture> textures_loaded;
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
    Model(std::string const&, bool gamma = false);
    void Draw(GLuint&);
  private:
    void loadModel(std::string const&);
    void processNode(aiNode*, const aiScene*);
    Mesh processMesh(aiMesh*, const aiScene*);
    vector<Texture> loadMaterialTextures(aiMaterial*,aiTextureType,std::string);
};
#endif
