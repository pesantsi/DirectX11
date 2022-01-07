#include "PPM.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

namespace PerlinLandscape
{
    //create a PPM object
    PPM::PPM()
    {
        Init();
    }

    //create a PPM object and fill it with data stored in fname 
    PPM::PPM(const std::string& fname)
    {
        Init();
        Read(fname);
    }

    //create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
    PPM::PPM(const unsigned int width, const unsigned int height)
    {
        Init();
        m_width = width;
        m_height = height;
        nr_lines = m_height;
        nr_columns = m_width;
        m_size = m_width * m_height;

        // fill r, g and b with 0
        m_r.resize(m_size);
        m_g.resize(m_size);
        m_b.resize(m_size);
    }

    void PPM::Init()
    {
        m_width = 0;
        m_height = 0;
        m_max_col_val = 255;
    }

    //read the PPM image from fname
    void PPM::Read(const std::string& fname)
    {
        std::ifstream inp(fname.c_str(), std::ios::in | std::ios::binary);
        if (inp.is_open()) {
            std::string line;
            std::getline(inp, line);
            if (line != "P6") {
                std::cout << "Error. Unrecognized file format." << std::endl;
                return;
            }
            std::getline(inp, line);
            while (line[0] == '#') {
                std::getline(inp, line);
            }
            std::stringstream dimensions(line);

            try {
                dimensions >> m_width;
                dimensions >> m_height;
                nr_lines = m_height;
                nr_columns = m_width;
            }
            catch (std::exception& e) {
                std::cout << "Header file format error. " << e.what() << std::endl;
                return;
            }

            std::getline(inp, line);
            std::stringstream max_val(line);
            try {
                max_val >> m_max_col_val;
            }
            catch (std::exception& e) {
                std::cout << "Header file format error. " << e.what() << std::endl;
                return;
            }

            m_size = m_width * m_height;

            m_r.reserve(m_size);
            m_g.reserve(m_size);
            m_b.reserve(m_size);

            char aux;
            for (unsigned int i = 0; i < m_size; ++i) {
                inp.read(&aux, 1);
                m_r[i] = (unsigned char)aux;
                inp.read(&aux, 1);
                m_g[i] = (unsigned char)aux;
                inp.read(&aux, 1);
                m_b[i] = (unsigned char)aux;
            }
        }
        else {
            std::cout << "Error. Unable to open " << fname << std::endl;
        }
        inp.close();
    }

    //write the PPM image in fname
    void PPM::Write(const std::string& fname)
    {
        std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
        if (inp.is_open()) {

            inp << "P6\n";
            inp << m_width;
            inp << " ";
            inp << m_height << "\n";
            inp << m_max_col_val << "\n";

            char aux;
            for (unsigned int i = 0; i < m_size; ++i) {
                aux = (char)m_r[i];
                inp.write(&aux, 1);
                aux = (char)m_g[i];
                inp.write(&aux, 1);
                aux = (char)m_b[i];
                inp.write(&aux, 1);
            }
        }
        else {
            std::cout << "Error. Unable to open " << fname << std::endl;
        }
        inp.close();
    }
}
