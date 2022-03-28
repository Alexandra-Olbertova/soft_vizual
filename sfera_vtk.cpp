#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    fstream vtkFile;

    vtkFile.open("sfera.vtk", ios::out);

    if (vtkFile.is_open()) {
        vtkFile << "# vtk DataFile Version 3.0\n";
        vtkFile << "Sfera\n";
        vtkFile << "ASCII\n";
        vtkFile << "DATASET POLYDATA\n";
       
        int s1 = 30, s2 = 30;
        vtkFile << "POINTS " << s1*s2 + 2 << " float\n";
    
        double k[30][30]; int i = 1;
        double theta = 0, dtheta = M_PI / s1;
        double phi = 0, dphi = 2 * M_PI / s2;
        double x, y, z;
        int r = 5;
        int tmp = 0;
        vtkFile << "0" << " 0 " << r << "\n";
        for (int ring = 0; ring < s1; ring++) {
            theta += dtheta;
            for (int point = 0; point < s2; point++) {
                if (ring == 0)
                    tmp++;

                phi += dphi;

                k[ring][point] = i;
                i++;

                x = r * sin(theta) * cos(phi);
                y = r * sin(theta) * sin(phi);
                z = r * cos(theta);

                vtkFile << x << " " << y << " " << z << "\n";
            }
        }
        vtkFile << "0" << " 0 " << -r << "\n";
  
        vtkFile << "POLYGONS " << 2 * (s1 - 1) * (s2 - 1) + tmp + 2 * (s2 - 1) << " " << 2 * 4 * (s1 - 1) * (s2 - 1) + tmp * 4 + 2 * (s2 - 1) * 4 << "\n";

        for (int i = 0; i < tmp - 1; i++) {
            vtkFile << "3 0 " << k[0][i] << " " << k[0][i+1] << "\n";
        }
        vtkFile << "3 0 1 " << tmp << "\n";

        for (int i = 0; i < s1 - 1; i++) {
            for (int j = 0; j < s2 - 1; j++) {
                vtkFile << "3 " << k[i][j] << " " << k[i][j + 1] << " " << k[i + 1][j] << "\n";
                vtkFile << "3 " << k[i][j + 1] << " " << k[i + 1][j] << " " << k[i + 1][j + 1] << "\n";

                if (j == s2 - 2) {
                    vtkFile << "3 " << k[i + 1][0] << " " << k[i][0] << " " << k[i + 1][j + 1] << "\n";
                    vtkFile << "3 " << k[i][j + 1] << " " << k[i][0] << " " << k[i + 1][j + 1] << "\n";
                }    
            }
        }        
    }
    else
        cout << "Subor sa nepodarilo otvorit" << endl;

    vtkFile.close();

    return 0;
}
