#include &lt;iostream&gt;
#include &lt;string&gt;
using namespace std;
struct HDD {
int cylinders;
int tracks_per_cylinder;
int sectors_per_track;
int bytes_per_sector;
long long totalCapacity() {
return (long long)cylinders * tracks_per_cylinder
* sectors_per_track * bytes_per_sector;
}
};
int main() {
HDD disk = {1024, 16, 63, 512};
cout &lt;&lt; &quot;Total Capacity: &quot; &lt;&lt; disk.totalCapacity() &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
return 0;
}
