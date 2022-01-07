#pragma once
//Process a binary PPM file
#include <vector>
#include <string>

namespace PerlinLandscape
{
    class PPM
    {
    public:
        PPM();
        //create a PPM object and fill it with data stored in fname 
        PPM(const std::string& fname);
        //create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
        PPM(const unsigned int width, const unsigned int height);
        //read the PPM image from fname
        void Read(const std::string& fname);
        //write the PPM image in fname
        void Write(const std::string& fname);

//         inline std::vector<unsigned char>& GetR() { return m_r; }
//         inline std::vector<unsigned char>& GetG() { return m_g; }
//         inline std::vector<unsigned char>& GetB() { return m_b; }
                //arrays for storing the R,G,B values
        std::vector<unsigned char> m_r;
        std::vector<unsigned char> m_g;
        std::vector<unsigned char> m_b;

    private:
        void Init();

        //info about the PPM file (height and width)
        unsigned int nr_lines;
        unsigned int nr_columns;

        //arrays for storing the R,G,B values
//         std::vector<unsigned char> m_r;
//         std::vector<unsigned char> m_g;
//         std::vector<unsigned char> m_b;
        //
        unsigned int m_height;
        unsigned int m_width;
        unsigned int m_max_col_val;
        //total number of elements (pixels)
        unsigned int m_size;
    };
}