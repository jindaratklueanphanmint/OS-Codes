#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;string&gt;
using namespace std;
class RAID {
int numDisks;
vector&lt;vector&lt;string&gt;&gt; disks;
public:
RAID(int n) : numDisks(n), disks(n) {}
// RAID-0: stripe data across disks
void writeRAID0(string data) {
for (int i = 0; i &lt; data.size(); i++)
disks[i % numDisks].push_back(string(1, data[i]));
}
// RAID-1: mirror data to all disks
void writeRAID1(string data) {
for (auto&amp; disk : disks)
disk.push_back(data);
}
void status() {
for (int i = 0; i &lt; numDisks; i++) {
cout &lt;&lt; &quot;Disk &quot; &lt;&lt; i &lt;&lt; &quot;: &quot;;
for (auto&amp; b : disks[i]) cout &lt;&lt; b &lt;&lt; &quot; &quot;;
cout &lt;&lt; endl;
}
}
};
int main() {
RAID r0(3);
r0.writeRAID0(&quot;ABCDEF&quot;);
cout &lt;&lt; &quot;=== RAID-0 ===&quot; &lt;&lt; endl; r0.status();
RAID r1(3);
r1.writeRAID1(&quot;BACKUP&quot;);
cout &lt;&lt; &quot;=== RAID-1 ===&quot; &lt;&lt; endl; r1.status();
return 0;
}
