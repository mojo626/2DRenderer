#ifndef PARTICLES_H
#define PARTICLES_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include "Shaders.hpp"

struct Particle
{
    glm::vec3 pos, speed;
    unsigned char r, g, b, a;
    float size, angle, weight;
    float life; //life of particle, when <0 particle is killed
};

const int maxParticles = 1000;

class ParticleSystem {
    public:
        Particle particlesContainer[maxParticles];
        int lastUsedparticle = 0;
        Shader shader;

        int FindUnusedParticle()
        {
            //look through particles until we find one that isn't used yet
            for (int i = lastUsedparticle; i < maxParticles; i++)
            {
                if (particlesContainer[i].life <= 0.0f)
                {
                    lastUsedparticle = i;
                    return i;
                }
            }

            //if there aren't any from where we left off to the end, start at the beginning and look util where we left off
            for (int i = 0; i < lastUsedparticle; i++)
            {
                if (particlesContainer[i].life <= 0.0f)
                {
                    lastUsedparticle = i;
                    return i;
                }
            }
            std::cout << "all particles used" << std::endl;
            //all particles are being used
            return 0;
        }

        //playerPos is just for testing
        void SimulateParticles(float deltaTime, glm::vec2 playerPos)
        {
            float numNew = 100.0;
            int newparticles = (int)(deltaTime*numNew);
            //clamp to 16ms frames so we don't spawn a lot of particles when there is a slow frame
            if (newparticles > (int)(0.016f*numNew))
                newparticles = (int)(0.016f*numNew);

            SpawnParticles(newparticles, playerPos);

            // Simulate all particles
            int ParticlesCount = 0;
            float delta = 0.1f;
            for(int i=0; i<maxParticles; i++){

                Particle& p = particlesContainer[i]; // shortcut

                if(p.life > 0.0f){

                    // Decrease life
                    p.life -= delta;
                    if (p.life > 0.0f){

                        // Simulate simple physics : gravity only, no collisions
                        //p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
                        //p.pos += p.speed * (float)delta;
                        //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

                        // Fill the GPU buffer
                        g_particle_position_size_data[4*ParticlesCount+0] = p.pos.x;
                        g_particle_position_size_data[4*ParticlesCount+1] = p.pos.y;

                        g_particle_position_size_data[4*ParticlesCount+3] = p.size;

                        g_particle_color_data[4*ParticlesCount+0] = p.r;
                        g_particle_color_data[4*ParticlesCount+1] = p.g;
                        g_particle_color_data[4*ParticlesCount+2] = p.b;
                        g_particle_color_data[4*ParticlesCount+3] = p.a;

                    }

                    ParticlesCount++;

                }
            }

            this->shader.use();
            UpdateBuffers(ParticlesCount);
            RenderParticles(ParticlesCount);
            glBindVertexArray(0);
        }

        void InitSystem(glm::mat4 *projection) {
            this->shader = Shader("../res/shaders/particle.vert", "../res/shaders/particle.frag");

            this->shader.use();

            this->shader.SetMatrix4("projection", *projection);

            g_particle_color_data = new int[4*maxParticles];
            g_particle_position_size_data = new int[4*maxParticles];

            // The VBO containing the 4 vertices of the particles.
            // Thanks to instancing, they will be shared by all particles.
            // static const GLfloat g_vertex_buffer_data[] = {
            // -0.5f, -0.5f, 0.0f,
            // 0.5f, -0.5f, 0.0f,
            // -0.5f, 0.5f, 0.0f,
            // 0.5f, 0.5f, 0.0f,
            // };
            static const GLfloat g_vertex_buffer_data[] = {
            // positions     // colors
            -0.05f,  0.05f,  0.0f, 
            0.05f, -0.05f,  0.0f, 
            -0.05f, -0.05f,  0.0f,

            -0.05f,  0.05f,  0.0f, 
            0.05f, -0.05f,  0.0f,   
            0.05f,  0.05f,  0.0f, 
            };
            glGenBuffers(1, &billboard_vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

            // The VBO containing the positions and sizes of the particles
            glGenBuffers(1, &particles_position_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
            // Initialize with empty (NULL) buffer : it will be updated later, each frame.
            glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

            // The VBO containing the colors of the particles
            glGenBuffers(1, &particles_color_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
            // Initialize with empty (NULL) buffer : it will be updated later, each frame.
            glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void UpdateBuffers(int ParticlesCount)
        {
            // Update the buffers that OpenGL uses for rendering.
            // There are much more sophisticated means to stream data from the CPU to the GPU,
            // but this is outside the scope of this tutorial.
            // http://www.opengl.org/wiki/Buffer_Object_Streaming

            glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
            glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
            glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particle_position_size_data);

            glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
            glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
            glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particle_color_data);
        }

        void RenderParticles(int ParticlesCount)
        {
            

            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
            glVertexAttribPointer(
            0, // attribute. No particular reason for 0, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            3 * sizeof(float), // stride
            (void*)0 // array buffer offset
            );

            // 2nd attribute buffer : positions of particles' centers
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
            glVertexAttribPointer(
            1, // attribute. No particular reason for 1, but must match the layout in the shader.
            4, // size : x + y + z + size => 4
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            4 * sizeof(float), // stride
            (void*)0 // array buffer offset
            );

            // 3rd attribute buffer : particles' colors
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
            glVertexAttribPointer(
            2, // attribute. No particular reason for 1, but must match the layout in the shader.
            4, // size : r + g + b + a => 4
            GL_UNSIGNED_BYTE, // type
            GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
            4 * sizeof(float), // stride
            (void*)0 // array buffer offset
            );


            // These functions are specific to glDrawArrays*Instanced*.
            // The first parameter is the attribute buffer we're talking about.
            // The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
            // http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
            glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
            glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
            glVertexAttribDivisor(2, 1); // color : one per quad -> 1

            // Draw the particules !
            // This draws many times a small triangle_strip (which looks like a quad).
            // This is equivalent to :
            // for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
            // but faster.
            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, ParticlesCount);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }

        void SpawnParticles(int newparticles, glm::vec2 playerPos)
        {
            for (int i = 0; i < newparticles; i++)
            {
                int particleIndex = FindUnusedParticle();

                Particle newParticle;
                newParticle.pos = glm::vec3(playerPos, 0);
                newParticle.speed = glm::vec3(-1, 0, 0);
                newParticle.life = 20.0;
                newParticle.a = 1.0;
                newParticle.r = 1.0;
                newParticle.g = 1.0;
                newParticle.b = 1.0;
                newParticle.size = 20.0f;


                particlesContainer[particleIndex] = newParticle;

            }
        }

        private:
            GLuint particles_color_buffer;
            GLuint particles_position_buffer;
            GLuint billboard_vertex_buffer;
            int* g_particle_color_data;
            int* g_particle_position_size_data;

};



#endif