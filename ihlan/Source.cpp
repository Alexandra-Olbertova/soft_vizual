#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    float h, r, n;
    r = 5;
    n = 5;
    h = 10;


    fstream vtkFile;

    vtkFile.open("ihlan.vtk", ios::out);
    
    if (vtkFile.is_open()) {

        vtkFile << "# vtk DataFile Version 3.0\n";
        vtkFile << "Ihlan\n";
        vtkFile << "ASCII\n";
        vtkFile << "DATASET POLYDATA\n";

        vtkFile << "POINTS " << n + 1 << " float\n";

        float newX = 0, newY = 0;
        float alpha = 0;

        for (int i = 0; i < n; i++) {
            newX += r * cos(alpha * 3.14 / 180);
            newY += r * sin(alpha * 3.14 / 180);

            vtkFile << newX << " " << newY << " " << "0\n";
            alpha += 360 / n;
        }
        vtkFile << "0 0 " << h << endl;

        vtkFile << "LINES " << 2 * n << " " << 2 * n * 3 << endl;
        for (int i = 0; i < n - 1; i++) {
            vtkFile << "2 " << i << " " << i + 1 << "\n";
            vtkFile << "2 " << i << " " << n << "\n";
        }

        vtkFile << "2 " << n - 1 << " 0\n";
        vtkFile << "2 " << n - 1 << " " << n << "\n";

        vtkFile << "POLYGONS " << n + 1 << " " << ((n + 1) * 4) + (n - 3) << "\n";
        for (int i = 0; i < n - 1; i++) {
            vtkFile << "3 " << i << " " << i + 1 << " " << n << "\n";
        }
        vtkFile << "3 " << n - 1 << " 0 " << n << "\n";
        vtkFile << n << " ";
        for (int i = 0; i < n; i++) {
            vtkFile << i << " ";
        }
        vtkFile << "\n";

        vtkFile.close();
    }
    else 
        cout << "Subor sa nepodarilo otvorit" << endl;
   




}
