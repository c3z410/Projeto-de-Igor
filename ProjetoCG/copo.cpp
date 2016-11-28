#include <camera.h>

/**
 * Contrutor vazio.*/
copo::copo(){}

copo::~copo(){
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteSamplers(1, &samp);
	glDeleteTextures(1, &text_gl_name);
	glDeleteTextures(1, &text_map);
}

/**
 * Carrega os dados do objeto em um buffer.
 * @param object_name nome do arquivo onde se encontram os dados.
 */
void copo::loadData(const std::string& object_name){
	
	load_grouped_data(base_data_location + object_name, triangle_count, data, false);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), (void*)data.data(), GL_STATIC_DRAW);

	glGenSamplers(1, &samp);
	glSamplerParameteri(samp, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(samp, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindSampler(text_target, samp);

	
}
/*
void copo::draw(){
	
	glBindTexture(text_target, text_gl_name);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_PATCHES, 0, 4);
}*/
