#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
int main()
{
    // create and read Polyhedron
    Polyhedron mesh;
    //-------------------------------input--------------------------------
    FILE * nfile = fopen("cup.off","r");
    float vertex[6][25002];
    int face[4][50000];
    std::string s;
    fscanf(nfile,"%s\n",&s);
    int a,b,c;
    fscanf(nfile,"%d %d %d\n",&a,&b,&c);
    for(int i=0;i<25002;i++)
    {
        fscanf(nfile,"%f %f %f\n",&vertex[0][i],&vertex[1][i],&vertex[2][i]);
       //std::cout<<vertex[0][i]<<" "<<vertex[1][i]<<" "<<vertex[2][i]<<std::endl;
    }
    for(int i=0;i<50000;i++)
    {
        fscanf(nfile,"%d %d %d %d\n",&face[0][i],&face[1][i],&face[2][i],&face[3][i]);
        //std::cout<<face[0][i]<<" "<<face[1][i]<<" "<<face[2][i]<<" "<<face[3][i]<<std::endl;
    }
    fclose(nfile);
    std::ifstream input("cup.off");
    if ( !input || !(input >> mesh) || mesh.empty() ) {
        std::cerr << "Not a valid off file." << std::endl;
        return EXIT_FAILURE;
    }
    // create a property-map for segment-ids
    typedef std::map<Polyhedron::Facet_const_handle, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    boost::associative_property_map<Facet_int_map> segment_property_map(internal_segment_map);
    // calculate SDF values and segment the mesh using default parameters.
    std::size_t number_of_segments = CGAL::segmentation_via_sdf_values(mesh, segment_property_map);
    std::cout << "Number of segments: " << number_of_segments << std::endl;
    // print segment-ids
    int count=0;
    int label[50000];
    for(Polyhedron::Facet_const_iterator facet_it = mesh.facets_begin();
        facet_it != mesh.facets_end(); ++facet_it) {
        //std::cout <<segment_property_map[facet_it] << " ";
        label[count]=segment_property_map[facet_it];
        count++;
    }
 
    
    std::cout << std::endl;
    FILE * wfile = fopen("bottle1.ply","wb");
    fprintf(wfile,"ply\n");
    fprintf(wfile,"format ascii 1.0\n");
    fprintf(wfile,"comment VCGLIB generated\n");
    fprintf(wfile,"element vertex %d\n",25002);
    fprintf(wfile,"property float x\n");
    fprintf(wfile,"property float y\n");
    fprintf(wfile,"property float z\n");
    fprintf(wfile,"property uchar red\n");
    fprintf(wfile,"property uchar green\n");
    fprintf(wfile,"property uchar blue\n");
    fprintf(wfile,"element face %d\n",50000);
    fprintf(wfile,"property list int int vertex_indices\n");
    fprintf(wfile,"end_header\n");
    int color[number_of_segments];
    for (int i=0;i<(number_of_segments+2);i++)
    {
        color[i]=rand()%255;
        std::cout<<color[i]<<std::endl;
    }

    for (int i=0;i<count;i++)
    {
        for (int j=0;j<number_of_segments;j++){
        if (label[i]==j)
        {
            vertex[3][face[1][i]]=color[j];
            vertex[4][face[1][i]]=color[j+1];
            vertex[5][face[1][i]]=color[j+2];
            vertex[3][face[2][i]]=color[j];
            vertex[4][face[2][i]]=color[j+1];
            vertex[5][face[2][i]]=color[j+2];
            vertex[3][face[3][i]]=color[j];
            vertex[4][face[3][i]]=color[j+1];
            vertex[5][face[3][i]]=color[j+2];
        }
      
        }
    }
    //fprintf(wfile,"OFF\n");
    //fprintf(wfile,"25002 50000 0\n");
    for(int i=0;i<25002;i++)
    {
        fprintf(wfile,"%f %f %f %d %d %d\n",vertex[0][i],vertex[1][i],vertex[2][i],uint8_t(vertex[3][i]),uint8_t(vertex[4][i]),uint8_t(vertex[5][i]));
    }
    for(int i=0;i<50000;i++)
    {
        fprintf(wfile,"%d %d %d %d\n",face[0][i],face[1][i],face[2][i],face[3][i]);
    }
    fclose(wfile);
    //std::cout << "Num of Labels: "<<count;
    
}



