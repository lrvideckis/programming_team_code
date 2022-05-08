#pragma once

//status: tested against output of dijkstras and SCC on random graphs
//
//**for directed graphs only** if you initialize len[i][i] to infinity, then
//afterwards, len[i][i] = length of shortest cycle including node `i`

for (int k = 0; k < n; k++) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			len[i][j] = min(len[i][j], len[i][k] + len[k][j]);
	}
}
