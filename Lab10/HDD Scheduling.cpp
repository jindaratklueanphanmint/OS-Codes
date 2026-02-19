#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;algorithm&gt;
#include &lt;cmath&gt;
using namespace std;
int sstf(int head, vector&lt;int&gt; requests) {
int totalMovement = 0;
while (!requests.empty()) {
int closest = 0;
for (int i = 1; i &lt; requests.size(); i++)
if (abs(requests[i]-head) &lt; abs(requests[closest]-head))
closest = i;
totalMovement += abs(requests[closest] - head);
head = requests[closest];
requests.erase(requests.begin() + closest);
}
return totalMovement;
}
int main() {
vector&lt;int&gt; req = {98, 183, 37, 122, 14, 124, 65, 67};
cout &lt;&lt; &quot;SSTF Total Head Movement: &quot; &lt;&lt; sstf(53, req) &lt;&lt; endl;
return 0;
}
