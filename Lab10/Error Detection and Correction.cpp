#include &lt;iostream&gt;
#include &lt;vector&gt;
using namespace std;
int computeParity(vector&lt;int&gt;&amp; bits) {
int parity = 0;
for (int b : bits) parity ^= b;
return parity;
}
bool checkParity(vector&lt;int&gt;&amp; data, int storedParity) {
return computeParity(data) == storedParity;
}
int main() {
vector&lt;int&gt; data = {1, 0, 1, 1, 0, 0, 1, 0};
int parity = computeParity(data);
cout &lt;&lt; &quot;Parity bit: &quot; &lt;&lt; parity &lt;&lt; endl;
// Simulate a 1-bit error
data[3] = 1 - data[3];
cout &lt;&lt; &quot;Error detected: &quot; &lt;&lt; !checkParity(data, parity) &lt;&lt; endl;
return 0;
}
