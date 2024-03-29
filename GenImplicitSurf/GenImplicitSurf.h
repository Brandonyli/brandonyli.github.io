#pragma once
#include "../Parsing/exprtk.hpp"
#include "Mesh.h"
#include <string>
#include <vector>

/* ----------SOURCE CODE----------
Inspiration and starter code for the Marching Cubes Algorithm is from Paul Bourke’s C++
implementation found here http://paulbourke.net/geometry/polygonise/.

Inspiration and starter code for combining the Marching Cubes Algorithm with ExprTk is from
Pablo Javier Antuna’s TriangSurf program http://w3.impa.br/~pabloant/triangulation-surfaces.html.
*/

namespace Nome::Scene
{

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;

typedef struct
{
    double x, y, z;
} Xyz;

typedef struct
{
    int p[3];
} Triangle;

typedef struct
{
    Xyz p[8];
    double val[8];
} Gridcell;

class CGenImplicitSurf : public CMesh

{
    DEFINE_INPUT(float, x_start) { MarkDirty(); }
    DEFINE_INPUT(float, x_end) { MarkDirty(); }
    DEFINE_INPUT(float, y_start) { MarkDirty(); }
    DEFINE_INPUT(float, y_end) { MarkDirty(); }
    DEFINE_INPUT(float, z_start) { MarkDirty(); }
    DEFINE_INPUT(float, z_end) { MarkDirty(); }
    DEFINE_INPUT(float, num_segs_x) { MarkDirty(); }
    DEFINE_INPUT(float, num_segs_y) { MarkDirty(); }
    DEFINE_INPUT(float, num_segs_z) { MarkDirty(); }

public:
    DECLARE_META_CLASS(CGenImplicitSurf, CMesh);
    CGenImplicitSurf() = default;
    CGenImplicitSurf(const std::string& name, const std::string& func)
        : CMesh(std::move(name))
        , Func(std::move(func))
    {
    }

    const std::string& GetFunc() const { return Func; }
    void UpdateEntity() override;

private:
    double functionXyz(double x, double y, double z);
    void runMarchingCubes(int gridSizeX, int gridSizeY, int gridSizeZ, double xMin, double yMin,
                          double zMin, double xMax, double yMax, double zMax);
    void addVerticesAndFaces(std::vector<Xyz> vertex, std::vector<Triangle> Triangles, int nv,
                             int nt);

    expression_t expression;
    symbol_table_t symbol_table;
    std::string Func;
};

}