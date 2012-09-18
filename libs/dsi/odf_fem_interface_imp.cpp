#include "tessellated_icosahedron.hpp"




std::vector<image::vector<3,float> > vertices;
std::vector<image::vector<3,short> > faces;
std::vector<std::vector<float> > icosa_cos;
//extern float icosa[162][3];
//extern float icosa181[181][3];
unsigned int vertices_count;
unsigned int faces_count;
unsigned int half_vertex_count;

extern "C"
{

    void ti_load_odf_vertices(unsigned int vertices_count_,const float* odf_buffer)
    {
        vertices_count = vertices_count_;
        half_vertex_count = vertices_count >> 1;
        vertices.resize(vertices_count);
        for (unsigned int index = 0;index < vertices_count;++index,odf_buffer += 3)
            vertices[index] = odf_buffer;
    }
    void ti_load_odf_faces(unsigned int faces_count_,const short* face_buffer)
    {
        faces_count = faces_count_;
        faces.resize(faces_count);
        for (unsigned int  index = 0;index < faces_count;++index,face_buffer += 3)
            faces[index] = face_buffer;
        icosa_cos.clear();
    }

    void ti_initialize(unsigned int fold)
    {
        vertices_count = fold*fold*10+2;
        faces_count = fold*fold*20;
        half_vertex_count = vertices_count >> 1;
        switch (fold)
        {
            /*case 0:
            	vertices_count = 162;
            	vertices.resize(162);
                for(unsigned int index = 0;index < 162;++index)
            		vertices[index] = icosa[index];
            	faces_count = 320;
            	faces.resize(320);
            	break;
            */
        case 4:
        {
            TessellatedIcosahedron<4> ti;
            ti.vertices.swap(vertices);
            ti.faces.swap(faces);
        }
        break;
        case 5:
        {
            TessellatedIcosahedron<5> ti;
            ti.vertices.swap(vertices);
            ti.faces.swap(faces);
        }
        break;
        case 6:
        {
            TessellatedIcosahedron<6> ti;
            ti.vertices.swap(vertices);
            ti.faces.swap(faces);
        }
        break;
        case 8:
        {
            TessellatedIcosahedron<8> ti;
            ti.vertices.swap(vertices);
            ti.faces.swap(faces);
        }
        break;
        }
    }


    unsigned int ti_vertices_count(void)
    {
        return vertices_count;
    }


    unsigned int ti_faces_count(void)
    {
        return faces_count;
    }


    float* ti_vertices(unsigned int index)
    {
        return vertices[index].begin();
    }


    short ti_vertices_pair(short v1)
    {
        return (v1 < half_vertex_count) ? v1 + half_vertex_count:v1 - half_vertex_count;
    }

    float ti_vertices_cos(unsigned int v1,unsigned int v2)
    {
        if(icosa_cos.empty())
        {
            icosa_cos.resize(vertices_count);
            for (unsigned int i = 0; i < vertices_count; ++i)
            {
                icosa_cos[i].resize(vertices_count);
                for (unsigned int j = 0; j < vertices_count; ++j)
                    icosa_cos[i][j] = vertices[i]*vertices[j];
            }
        }
        return icosa_cos[v1][v2];
    }

    short* ti_faces(unsigned int index)
    {
        return faces[index].begin();
    }



    short ti_discretize(float vx,float vy,float vz)
    {
        short dir_index = 0;
        float max_value = 0.0;
        image::vector<3,float> v(vx,vy,vz);
        for (unsigned int index = 0; index < vertices_count; ++index)
        {
            float value = vertices[index]*v;
            if (value > max_value)
            {
                max_value = value;
                dir_index = index;
            }
        }
        return dir_index;
    }

}


/*
float icosa[162][3]={
{0,0,1.0000},
{0.8944,0,0.4472},
{0.2764,0.8507,0.4472},
{-0.7236,0.5257,0.4472},
{-0.7236,-0.5257,0.4472},
{0.2764,-0.8507,0.4472},
{0,0,-1.0000},
{0.7236,0.5257,-0.4472},
{-0.2764,0.8507,-0.4472},
{-0.8944,0.0000,-0.4472},
{-0.2764,-0.8507,-0.4472},
{0.7236,-0.5257,-0.4472},
{0.5257,0,0.8507},
{0.1625,0.5000,0.8507},
{0.6882,0.5000,0.5257},
{-0.4253,0.3090,0.8507},
{-0.2629,0.8090,0.5257},
{-0.4253,-0.3090,0.8507},
{-0.8507,0.0000,0.5257},
{0.1625,-0.5000,0.8507},
{0.6882,-0.5000,0.5257},
{-0.2629,-0.8090,0.5257},
{0.9511,0.3090,0},
{0.5878,0.8090,0},
{0.4253,0.3090,-0.8507},
{0.0000,1.0000,0},
{-0.5878,0.8090,0},
{-0.1625,0.5000,-0.8507},
{0.2629,0.8090,-0.5257},
{-0.9511,0.3090,0},
{-0.9511,-0.3090,0},
{-0.5257,0.0000,-0.8507},
{-0.6882,0.5000,-0.5257},
{-0.5878,-0.8090,0},
{-0.0000,-1.0000,0},
{-0.1625,-0.5000,-0.8507},
{-0.6882,-0.5000,-0.5257},
{0.9511,-0.3090,0},
{0.5878,-0.8090,0},
{0.4253,-0.3090,-0.8507},
{0.8507,-0.0000,-0.5257},
{0.2629,-0.8090,-0.5257},
{0.2733,0,0.9619},
{0.7382,0,0.6746},
{0.0844,0.2599,0.9619},
{0.2281,0.7020,0.6746},
{0.3618,0.2629,0.8944},
{0.8226,0.2599,0.5057},
{0.5014,0.7020,0.5057},
{0.6382,0.2629,0.7236},
{0.4472,0.5257,0.7236},
{-0.2211,0.1606,0.9619},
{-0.5972,0.4339,0.6746},
{-0.1382,0.4253,0.8944},
{0.0070,0.8627,0.5057},
{-0.5128,0.6938,0.5057},
{-0.0528,0.6882,0.7236},
{-0.3618,0.5878,0.7236},
{-0.2211,-0.1606,0.9619},
{-0.5972,-0.4339,0.6746},
{-0.4472,0.0000,0.8944},
{-0.8183,0.2733,0.5057},
{-0.8183,-0.2733,0.5057},
{-0.6708,0.1625,0.7236},
{-0.6708,-0.1625,0.7236},
{0.0844,-0.2599,0.9619},
{0.2281,-0.7020,0.6746},
{0.3618,-0.2629,0.8944},
{-0.1382,-0.4253,0.8944},
{0.8226,-0.2599,0.5057},
{0.5014,-0.7020,0.5057},
{0.6382,-0.2629,0.7236},
{0.4472,-0.5257,0.7236},
{-0.5128,-0.6938,0.5057},
{0.0070,-0.8627,0.5057},
{-0.3618,-0.5878,0.7236},
{-0.0528,-0.6882,0.7236},
{0.9593,0.1606,0.2325},
{0.8705,0.4339,-0.2325},
{0.8618,0.4253,0.2764},
{0.4492,0.8627,0.2325},
{0.6816,0.6938,-0.2325},
{0.6708,0.6882,0.2764},
{0.8090,0.5878,0},
{0.2211,0.1606,-0.9619},
{0.5972,0.4339,-0.6746},
{0.1437,0.9619,0.2325},
{-0.1437,0.9619,-0.2325},
{-0.1382,0.9511,0.2764},
{0.3090,0.9511,0},
{-0.6816,0.6938,0.2325},
{-0.4492,0.8627,-0.2325},
{-0.4472,0.8507,0.2764},
{-0.3090,0.9511,0},
{-0.0844,0.2599,-0.9619},
{-0.2281,0.7020,-0.6746},
{0.1382,0.4253,-0.8944},
{0.5128,0.6938,-0.5057},
{-0.0070,0.8627,-0.5057},
{0.4472,0.8507,-0.2764},
{0.3618,0.5878,-0.7236},
{0.1382,0.9511,-0.2764},
{0.0528,0.6882,-0.7236},
{-0.8705,0.4339,0.2325},
{-0.9593,0.1606,-0.2325},
{-0.9472,0.1625,0.2764},
{-0.8090,0.5878,0},
{-0.8705,-0.4339,0.2325},
{-0.9593,-0.1606,-0.2325},
{-0.9472,-0.1625,0.2764},
{-1.0000,0.0000,0},
{-0.2733,0.0000,-0.9619},
{-0.7382,0.0000,-0.6746},
{-0.3618,0.2629,-0.8944},
{-0.5014,0.7020,-0.5057},
{-0.8226,0.2599,-0.5057},
{-0.6708,0.6882,-0.2764},
{-0.4472,0.5257,-0.7236},
{-0.8618,0.4253,-0.2764},
{-0.6382,0.2629,-0.7236},
{-0.6816,-0.6938,0.2325},
{-0.4492,-0.8627,-0.2325},
{-0.4472,-0.8507,0.2764},
{-0.8090,-0.5878,0},
{0.1437,-0.9619,0.2325},
{-0.1437,-0.9619,-0.2325},
{-0.1382,-0.9511,0.2764},
{-0.3090,-0.9511,0},
{-0.0844,-0.2599,-0.9619},
{-0.2281,-0.7020,-0.6746},
{-0.3618,-0.2629,-0.8944},
{-0.8226,-0.2599,-0.5057},
{-0.5014,-0.7020,-0.5057},
{-0.8618,-0.4253,-0.2764},
{-0.6382,-0.2629,-0.7236},
{-0.6708,-0.6882,-0.2764},
{-0.4472,-0.5257,-0.7236},
{0.9593,-0.1606,0.2325},
{0.8705,-0.4339,-0.2325},
{0.8618,-0.4253,0.2764},
{1.0000,-0.0000,0},
{0.4492,-0.8627,0.2325},
{0.6816,-0.6938,-0.2325},
{0.6708,-0.6882,0.2764},
{0.3090,-0.9511,0},
{0.8090,-0.5878,0},
{0.2211,-0.1606,-0.9619},
{0.5972,-0.4339,-0.6746},
{0.4472,-0.0000,-0.8944},
{0.1382,-0.4253,-0.8944},
{0.8183,0.2733,-0.5057},
{0.8183,-0.2733,-0.5057},
{0.9472,0.1625,-0.2764},
{0.6708,0.1625,-0.7236},
{0.9472,-0.1625,-0.2764},
{0.6708,-0.1625,-0.7236},
{-0.0070,-0.8627,-0.5057},
{0.5128,-0.6938,-0.5057},
{0.1382,-0.9511,-0.2764},
{0.0528,-0.6882,-0.7236},
{0.4472,-0.8507,-0.2764},
{0.3618,-0.5878,-0.7236}};



float icosa181[181][3]={{0., 0., 1.}, {0., 1., 0.}, {0.0206847, -0.936339,
 0.350487}, {0.0206847, 0.936339, 0.350487}, {0.0216227, -0.630351,
 0.776009}, {0.0216227, 0.630351,
 0.776009}, {0.0349863, -0.456127, -0.889227}, {0.0349863,
 0.456127, -0.889227}, {0.0500698, -0.154099, 0.986786}, {0.0500698,
 0.154099, 0.986786}, {0.0655604, -0.854729, -0.514918}, {0.0655604,
 0.854729, -0.514918}, {0.074838, -0.769672, 0.634038}, {0.074838,
 0.769672, 0.634038}, {0.0876219, -0.269672, -0.958957}, {0.0876219,
 0.269672, -0.958957}, {0.0915954, -0.978801, -0.183191}, {0.0915954,
  0.978801, -0.183191}, {0.106079, -0.979432, 0.171639}, {0.106079,
 0.979432, 0.171639}, {0.106079, -0.326477, 0.939234}, {0.106079,
 0.326477, 0.939234}, {0.119265, -0.865734, 0.486088}, {0.119265,
 0.865734, 0.486088}, {0.126582, -0.738028, -0.662791}, {0.126582,
 0.738028, -0.662791}, {0.131084, -0.0952384, -0.986786}, {0.131084,
 0.0952384, -0.986786}, {0.162029, 0., 0.986786}, {0.16246, -0.5,
 0.850651}, {0.16246, 0.5,
 0.850651}, {0.183191, -0.912253, -0.366382}, {0.183191,
 0.912253, -0.366382}, {0.187592, -0.57735, -0.794654}, {0.187592,
 0.57735, -0.794654}, {0.200279, -0.924594, 0.324059}, {0.200279,
 0.924594, 0.324059}, {0.204814, -0.978801, 0.}, {0.204814, 0.978801,
  0.}, {0.212158, -0.652955, 0.727076}, {0.212158, 0.652955,
 0.727076}, {0.229397, -0.166667, 0.958957}, {0.229397, 0.166667,
 0.958957}, {0.2398, -0.389579, -0.889227}, {0.2398,
 0.389579, -0.889227}, {0.250349, -0.770495, 0.586227}, {0.250349,
 0.770495, 0.586227}, {0.262866, -0.809017, -0.525731}, {0.262866,
 0.809017, -0.525731}, {0.276393, -0.850651, 0.447214}, {0.276393,
 0.850651, 0.447214}, {0.277718, -0.201774, -0.939234}, {0.277718,
 0.201774, -0.939234}, {0.28355, 0., -0.958957}, {0.296409, -0.34845,
  0.889227}, {0.296409, 0.34845,
 0.889227}, {0.303531, -0.934172, -0.187592}, {0.303531,
 0.934172, -0.187592}, {0.304235, -0.936339, 0.175244}, {0.304235,
 0.936339, 0.175244}, {0.331395, -0.67148, -0.662791}, {0.331395,
 0.67148, -0.662791}, {0.343279, 0., 0.939234}, {0.353018, -0.522674,
  0.776009}, {0.353018, 0.522674, 0.776009}, {0.381433, -0.865734,
 0.324059}, {0.381433, 0.865734,
 0.324059}, {0.388004, -0.845705, -0.366382}, {0.388004, -0.497255, \
-0.776009}, {0.388004, 0.497255, -0.776009}, {0.388004,
 0.845705, -0.366382}, {0.391857, -0.666667, 0.634038}, {0.391857,
 0.666667, 0.634038}, {0.409627, -0.912253, 0.}, {0.409627, 0.912253,
  0.}, {0.412378, -0.770495, 0.486088}, {0.412378, 0.770495,
 0.486088}, {0.422991, -0.174225, 0.889227}, {0.422991, 0.174225,
 0.889227}, {0.425325, -0.309017, -0.850651}, {0.425325,
 0.309017, -0.850651}, {0.444613, -0.107677, -0.889227}, {0.444613,
 0.107677, -0.889227}, {0.449358, -0.730026, -0.514918}, {0.449358,
 0.730026, -0.514918}, {0.489876, -0.854729, 0.171639}, {0.489876,
 0.854729, 0.171639}, {0.491123, -0.356822, 0.794654}, {0.491123,
 0.356822, 0.794654}, {0.501223, -0.845705, -0.183191}, {0.501223,
 0.845705, -0.183191}, {0.512947, -0.578689, -0.634038}, {0.512947,
 0.578689, -0.634038}, {0.525731, 0.,
 0.850651}, {0.533632, -0.769672, 0.350487}, {0.533632, 0.769672,
 0.350487}, {0.536209, -0.522674, 0.662791}, {0.536209, 0.522674,
 0.662791}, {0.555436, -0.652955,
 0.514918}, {0.555436, -0.403548, -0.727076}, {0.555436,
 0.403548, -0.727076}, {0.555436, 0.652955,
 0.514918}, {0.567101, -0.745356, -0.350487}, {0.567101,
 0.745356, -0.350487}, {0.587785, -0.809017, 0.}, {0.587785,
 0.809017, 0.}, {0.592818, -0.215354, -0.776009}, {0.592818,
 0.215354, -0.776009}, {0.605352, -0.630291, -0.486088}, {0.605352,
 0.630291, -0.486088}, {0.606182, -0.174225, 0.776009}, {0.606182,
 0.174225, 0.776009}, {0.607062,
 0., -0.794654}, {0.649427, -0.738028, 0.183191}, {0.649427,
 0.738028, 0.183191}, {0.655422, -0.476192, -0.586227}, {0.655422,
 0.476192, -0.586227}, {0.661515, -0.730026, -0.171639}, {0.661515,
 0.730026, -0.171639}, {0.662791, -0.34845, 0.662791}, {0.662791,
 0.34845, 0.662791}, {0.684413, -0.630351, 0.366382}, {0.684413,
 0.630351, 0.366382}, {0.686557, 0., 0.727076}, {0.688191, -0.5,
 0.525731}, {0.688191, 0.5,
 0.525731}, {0.705492, -0.630291, -0.324059}, {0.705492,
 0.630291, -0.324059}, {0.708876, -0.309017, -0.634038}, {0.708876,
 0.309017, -0.634038}, {0.723607, -0.525731, -0.447214}, {0.723607,
 0.525731, -0.447214}, {0.741022, -0.67148, 0.}, {0.741022, 0.67148,
 0.}, {0.741022, -0.107677, -0.662791}, {0.741022,
 0.107677, -0.662791}, {0.755128, -0.166667, 0.634038}, {0.755128,
 0.166667, 0.634038}, {0.786507, -0.380954, -0.486088}, {0.786507,
 0.380954, -0.486088}, {0.792636, -0.326477, 0.514918}, {0.792636,
 0.326477, 0.514918}, {0.794654, -0.57735, 0.187592}, {0.794654,
 0.57735, 0.187592}, {0.796498, -0.578689, -0.175244}, {0.796498,
 0.578689, -0.175244}, {0.810146, 0.,
 0.586227}, {0.810995, -0.456127, 0.366382}, {0.810995, 0.456127,
 0.366382}, {0.817452, -0.476192, -0.324059}, {0.817452,
 0.476192, -0.324059}, {0.833155, -0.201774, -0.514918}, {0.833155,
 0.201774, -0.514918}, {0.850651,
 0., -0.525731}, {0.860216, -0.154099, 0.486088}, {0.860216,
 0.154099, 0.486088}, {0.867604, -0.497255, 0.}, {0.867604, 0.497255,
  0.}, {0.884119, -0.309017, -0.350487}, {0.884119,
 0.309017, -0.350487}, {0.894427, 0.,
 0.447214}, {0.896903, -0.269672, 0.350487}, {0.896903, 0.269672,
 0.350487}, {0.898715, -0.403548, -0.171639}, {0.898715,
 0.403548, -0.171639}, {0.902591, -0.389579, 0.183191}, {0.902591,
 0.389579, 0.183191}, {0.924213, -0.107677, -0.366382}, {0.924213,
 0.107677, -0.366382}, {0.941231, -0.0952384, 0.324059}, {0.941231,
 0.0952384, 0.324059}, {0.951057, -0.309017, 0.}, {0.951057,
 0.309017, 0.}, {0.9592, -0.215354, -0.183191}, {0.9592,
 0.215354, -0.183191}, {0.964275, -0.201774, 0.171639}, {0.964275,
 0.201774, 0.171639}, {0.982247, 0., -0.187592}, {0.984525, 0.,
 0.175244}, {0.994186, -0.107677, 0.}, {0.994186, 0.107677, 0.}};


/*
[0. 0. 1.; 0. 1. 0.;
 0.0206847 -0.936339 0.350487;
 0.0206847 0.936339 0.350487;
 0.0216227 -0.630351 0.776009;
 0.0216227 0.630351 0.776009;
 0.0349863 -0.456127 -0.889227;
 0.0349863 0.456127 -0.889227;
 0.0500698 -0.154099 0.986786;
 0.0500698 0.154099 0.986786;
 0.0655604 -0.854729 -0.514918;
 0.0655604 0.854729 -0.514918;
 0.074838 -0.769672 0.634038;
 0.074838 0.769672 0.634038;
 0.0876219 -0.269672 -0.958957;
 0.0876219 0.269672 -0.958957;
 0.0915954 -0.978801 -0.183191;
 0.0915954  0.978801 -0.183191;
 0.106079 -0.979432 0.171639;
 0.106079 0.979432 0.171639;
 0.106079 -0.326477 0.939234;
 0.106079 0.326477 0.939234;
 0.119265 -0.865734 0.486088;
 0.119265 0.865734 0.486088;
 0.126582 -0.738028 -0.662791;
 0.126582 0.738028 -0.662791;
 0.131084 -0.0952384 -0.986786;
 0.131084 0.0952384 -0.986786;
 0.162029 0. 0.986786;
 0.16246 -0.5 0.850651;
 0.16246 0.5 0.850651;
 0.183191 -0.912253 -0.366382;
 0.183191 0.912253 -0.366382;
 0.187592 -0.57735 -0.794654;
 0.187592 0.57735 -0.794654;
 0.200279 -0.924594 0.324059;
 0.200279 0.924594 0.324059;
 0.204814 -0.978801 0.;
 0.204814 0.978801  0.;
 0.212158 -0.652955 0.727076;
 0.212158 0.652955 0.727076;
 0.229397 -0.166667 0.958957;
 0.229397 0.166667 0.958957;
 0.2398 -0.389579 -0.889227;
 0.2398 0.389579 -0.889227;
 0.250349 -0.770495 0.586227;
 0.250349 0.770495 0.586227;
 0.262866 -0.809017 -0.525731;
 0.262866 0.809017 -0.525731;
 0.276393 -0.850651 0.447214;
 0.276393 0.850651 0.447214;
 0.277718 -0.201774 -0.939234;
 0.277718 0.201774 -0.939234;
 0.28355 0. -0.958957;
 0.296409 -0.34845  0.889227;
 0.296409 0.34845 0.889227;
 0.303531 -0.934172 -0.187592;
 0.303531 0.934172 -0.187592;
 0.304235 -0.936339 0.175244;
 0.304235 0.936339 0.175244;
 0.331395 -0.67148 -0.662791;
 0.331395 0.67148 -0.662791;
 0.343279 0. 0.939234;
 0.353018 -0.522674  0.776009;
 0.353018 0.522674 0.776009;
 0.381433 -0.865734 0.324059;
 0.381433 0.865734 0.324059;
 0.388004 -0.845705 -0.366382;
 0.388004 -0.497255 -0.776009;
 0.388004 0.497255 -0.776009;
 0.388004 0.845705 -0.366382;
 0.391857 -0.666667 0.634038;
 0.391857 0.666667 0.634038;
 0.409627 -0.912253 0.;
 0.409627 0.912253  0.;
 0.412378 -0.770495 0.486088;
 0.412378 0.770495 0.486088;
 0.422991 -0.174225 0.889227;
 0.422991 0.174225 0.889227;
 0.425325 -0.309017 -0.850651;
 0.425325 0.309017 -0.850651;
 0.444613 -0.107677 -0.889227;
 0.444613 0.107677 -0.889227;
 0.449358 -0.730026 -0.514918;
 0.449358 0.730026 -0.514918;
 0.489876 -0.854729 0.171639;
 0.489876 0.854729 0.171639;
 0.491123 -0.356822 0.794654;
 0.491123 0.356822 0.794654;
 0.501223 -0.845705 -0.183191;
 0.501223 0.845705 -0.183191;
 0.512947 -0.578689 -0.634038;
 0.512947 0.578689 -0.634038;
 0.525731 0. 0.850651;
 0.533632 -0.769672 0.350487;
 0.533632 0.769672 0.350487;
 0.536209 -0.522674 0.662791;
 0.536209 0.522674 0.662791;
 0.555436 -0.652955 0.514918;
 0.555436 -0.403548 -0.727076;
 0.555436 0.403548 -0.727076;
 0.555436 0.652955 0.514918;
 0.567101 -0.745356 -0.350487;
 0.567101 0.745356 -0.350487;
 0.587785 -0.809017 0.;
 0.587785 0.809017 0.;
 0.592818 -0.215354 -0.776009;
 0.592818 0.215354 -0.776009;
 0.605352 -0.630291 -0.486088;
 0.605352 0.630291 -0.486088;
 0.606182 -0.174225 0.776009;
 0.606182 0.174225 0.776009;
 0.607062 0. -0.794654;
 0.649427 -0.738028 0.183191;
 0.649427 0.738028 0.183191;
 0.655422 -0.476192 -0.586227;
 0.655422 0.476192 -0.586227;
 0.661515 -0.730026 -0.171639;
 0.661515 0.730026 -0.171639;
 0.662791 -0.34845 0.662791;
 0.662791 0.34845 0.662791;
 0.684413 -0.630351 0.366382;
 0.684413 0.630351 0.366382;
 0.686557 0. 0.727076;
 0.688191 -0.5 0.525731;
 0.688191 0.5 0.525731;
 0.705492 -0.630291 -0.324059;
 0.705492 0.630291 -0.324059;
 0.708876 -0.309017 -0.634038;
 0.708876 0.309017 -0.634038;
 0.723607 -0.525731 -0.447214;
 0.723607 0.525731 -0.447214;
 0.741022 -0.67148 0.;
 0.741022 0.67148 0.;
 0.741022 -0.107677 -0.662791;
 0.741022 0.107677 -0.662791;
 0.755128 -0.166667 0.634038;
 0.755128 0.166667 0.634038;
 0.786507 -0.380954 -0.486088;
 0.786507 0.380954 -0.486088;
 0.792636 -0.326477 0.514918;
 0.792636 0.326477 0.514918;
 0.794654 -0.57735 0.187592;
 0.794654 0.57735 0.187592;
 0.796498 -0.578689 -0.175244;
 0.796498 0.578689 -0.175244;
 0.810146 0. 0.586227;
 0.810995 -0.456127 0.366382;
 0.810995 0.456127 0.366382;
 0.817452 -0.476192 -0.324059;
 0.817452 0.476192 -0.324059;
 0.833155 -0.201774 -0.514918;
 0.833155 0.201774 -0.514918;
 0.850651 0. -0.525731;
 0.860216 -0.154099 0.486088;
 0.860216 0.154099 0.486088;
 0.867604 -0.497255 0.;
 0.867604 0.497255  0.;
 0.884119 -0.309017 -0.350487;
 0.884119 0.309017 -0.350487;
 0.894427 0. 0.447214;
 0.896903 -0.269672 0.350487;
 0.896903 0.269672 0.350487;
 0.898715 -0.403548 -0.171639;
 0.898715 0.403548 -0.171639;
 0.902591 -0.389579 0.183191;
 0.902591 0.389579 0.183191;
 0.924213 -0.107677 -0.366382;
 0.924213 0.107677 -0.366382;
 0.941231 -0.0952384 0.324059;
 0.941231 0.0952384 0.324059;
 0.951057 -0.309017 0.;
 0.951057 0.309017 0.;
 0.9592 -0.215354 -0.183191;
 0.9592 0.215354 -0.183191;
 0.964275 -0.201774 0.171639;
 0.964275 0.201774 0.171639;
 0.982247 0. -0.187592;
 0.984525 0. 0.175244;
 0.994186 -0.107677 0.;
 0.994186 0.107677 0.]
*/