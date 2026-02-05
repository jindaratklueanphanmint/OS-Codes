#include &lt;iostream&gt;
#include &lt;queue&gt;
#include &lt;unordered_set&gt;
#include &lt;vector&gt;
#include &lt;iomanip&gt;
using namespace std;
class PageReplacementFIFO {
private:
int numFrames;
queue&lt;int&gt; frameQueue;
unordered_set&lt;int&gt; frameSet;
int pageFaults;

vector&lt;vector&lt;int&gt;&gt; frameHistory; // Track frame contents over time
public:
PageReplacementFIFO(int frames) : numFrames(frames), pageFaults(0) {}
void referencePage(int page) {
cout &lt;&lt; &quot;\nReferencing page: &quot; &lt;&lt; page &lt;&lt; endl;
// Check if page is already in memory
if (frameSet.find(page) != frameSet.end()) {
cout &lt;&lt; &quot; Page &quot; &lt;&lt; page &lt;&lt; &quot; already in memory (HIT)&quot; &lt;&lt; endl;
} else {
// Page fault occurs
pageFaults++;
cout &lt;&lt; &quot; PAGE FAULT #&quot; &lt;&lt; pageFaults &lt;&lt; endl;
// If frames are full, remove oldest page (FIFO)
if (frameQueue.size() &gt;= numFrames) {
int removedPage = frameQueue.front();
frameQueue.pop();
frameSet.erase(removedPage);
cout &lt;&lt; &quot; Removed page &quot; &lt;&lt; removedPage &lt;&lt; &quot; (oldest)&quot; &lt;&lt; endl;
}
// Add new page
frameQueue.push(page);
frameSet.insert(page);
cout &lt;&lt; &quot; Loaded page &quot; &lt;&lt; page &lt;&lt; &quot; into memory&quot; &lt;&lt; endl;
}
// Record current frame contents
vector&lt;int&gt; currentFrames;
queue&lt;int&gt; tempQueue = frameQueue;
while (!tempQueue.empty()) {
currentFrames.push_back(tempQueue.front());
tempQueue.pop();
}
frameHistory.push_back(currentFrames);
// Display current frames
cout &lt;&lt; &quot; Frames: [&quot;;
for (size_t i = 0; i &lt; currentFrames.size(); i++) {
cout &lt;&lt; currentFrames[i];
if (i &lt; currentFrames.size() - 1) cout &lt;&lt; &quot;, &quot;;
}
cout &lt;&lt; &quot;]&quot; &lt;&lt; endl;
}
void simulate(vector&lt;int&gt; referenceString) {
cout &lt;&lt; &quot;\n========== FIFO PAGE REPLACEMENT SIMULATION ==========&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Number of Frames: &quot; &lt;&lt; numFrames &lt;&lt; endl;
cout &lt;&lt; &quot;Reference String: &quot;;
for (int page : referenceString) {
cout &lt;&lt; page &lt;&lt; &quot; &quot;;
}
cout &lt;&lt; &quot;\n&quot; &lt;&lt; endl;
// Process each page reference
for (int page : referenceString) {
referencePage(page);
}
displayResults();
displayTable(referenceString);
}

void displayResults() {
cout &lt;&lt; &quot;\n========== RESULTS ==========&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Total Page Faults: &quot; &lt;&lt; pageFaults &lt;&lt; endl;
int totalReferences = frameHistory.size();
double faultRate = (double)pageFaults / totalReferences * 100;
double hitRate = 100.0 - faultRate;
cout &lt;&lt; &quot;Total References: &quot; &lt;&lt; totalReferences &lt;&lt; endl;
cout &lt;&lt; &quot;Page Fault Rate: &quot; &lt;&lt; fixed &lt;&lt; setprecision(2)
&lt;&lt; faultRate &lt;&lt; &quot;%&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Hit Rate: &quot; &lt;&lt; hitRate &lt;&lt; &quot;%&quot; &lt;&lt; endl;
}
void displayTable(vector&lt;int&gt; referenceString) {
cout &lt;&lt; &quot;\n========== FRAME CONTENTS TABLE ==========&quot; &lt;&lt; endl;
cout &lt;&lt; setw(8) &lt;&lt; &quot;Step&quot; &lt;&lt; &quot; | &quot;;
for (size_t i = 0; i &lt; referenceString.size(); i++) {
cout &lt;&lt; setw(4) &lt;&lt; referenceString[i];
}
cout &lt;&lt; endl;
cout &lt;&lt; string(8 + 5 + referenceString.size() * 4, &#39;-&#39;) &lt;&lt; endl;
for (int frame = 0; frame &lt; numFrames; frame++) {
cout &lt;&lt; setw(8) &lt;&lt; (&quot;Frame &quot; + to_string(frame)) &lt;&lt; &quot; | &quot;;
for (size_t step = 0; step &lt; frameHistory.size(); step++) {
if (frame &lt; frameHistory[step].size()) {
cout &lt;&lt; setw(4) &lt;&lt; frameHistory[step][frame];
} else {
cout &lt;&lt; setw(4) &lt;&lt; &quot;-&quot;;
}
}
cout &lt;&lt; endl;
}
}
};
int main() {
cout &lt;&lt; &quot;PAGE REPLACEMENT ALGORITHM - FIFO&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;==================================&quot; &lt;&lt; endl;
// Test Case 1
cout &lt;&lt; &quot;\n--- TEST CASE 1 ---&quot; &lt;&lt; endl;
PageReplacementFIFO fifo1(3);
vector&lt;int&gt; refString1 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
fifo1.simulate(refString1);
// Test Case 2
cout &lt;&lt; &quot;\n\n--- TEST CASE 2 ---&quot; &lt;&lt; endl;
PageReplacementFIFO fifo2(4);
vector&lt;int&gt; refString2 = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
fifo2.simulate(refString2);
// Interactive mode
char choice;
cout &lt;&lt; &quot;\n\nRun custom test? (y/n): &quot;;
cin &gt;&gt; choice;
if (choice == &#39;y&#39; || choice == &#39;Y&#39;) {
int frames;
cout &lt;&lt; &quot;Enter number of frames: &quot;;
cin &gt;&gt; frames;
PageReplacementFIFO customFifo(frames);
cout &lt;&lt; &quot;Enter reference string (space-separated, -1 to end):&quot; &lt;&lt; endl;

vector&lt;int&gt; customRef;
int page;
while (cin &gt;&gt; page &amp;&amp; page != -1) {
customRef.push_back(page);
}
customFifo.simulate(customRef);
}
return 0;
}
