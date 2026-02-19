#include &lt;iostream&gt;
#include &lt;string&gt;
using namespace std;
class StorageDevice {
public:
virtual string getInterface() = 0;
virtual double getBandwidth() = 0; // MB/s
virtual void read(int lba) {
cout &lt;&lt; getInterface() &lt;&lt; &quot;: Reading LBA &quot; &lt;&lt; lba
&lt;&lt; &quot; at &quot; &lt;&lt; getBandwidth() &lt;&lt; &quot; MB/s&quot; &lt;&lt; endl;
}
virtual ~StorageDevice() {}
};
class SATADrive : public StorageDevice {
public:
string getInterface() override { return &quot;SATA&quot;; }
double getBandwidth() override { return 600.0; }
};
class NVMeDrive : public StorageDevice {
public:
string getInterface() override { return &quot;NVMe&quot;; }
double getBandwidth() override { return 7000.0; }
};
int main() {
StorageDevice* d1 = new SATADrive();
StorageDevice* d2 = new NVMeDrive();
d1-&gt;read(100); d2-&gt;read(100);
delete d1; delete d2;
return 0;
}
