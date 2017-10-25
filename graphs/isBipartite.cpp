unordered_map<string, bool> color;
unordered_map<string, bool> marked;
bool isBipartite(unordered_map<string, vector<string> > &adj, string v) {
   queue<string> q;
   q.push(v);
   marked[v] = true;
   color[v] = true;//this is arbitrary
   while(!q.empty()) {
      v = q.front();
      q.pop();
      for(string x : adj[v]) {
         if(!marked[x]) {
            q.push(x);
            marked[x] = true;
            color[x] = !color[v];
         } else {//need to check for bipartiteness
            if(color[x] == color[v]) return  false;
         }
      }
   }
   return true;
}
