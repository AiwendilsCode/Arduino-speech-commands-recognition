const byte nBand = 6;
// frequencies: 100, 180, 325, 585, 1054, 1900
const long filt_a0[nBand+1] = {1501, 2650, 4593, 7667, 11820, 15038};
const long filt_b1[nBand+1] = {-127676, -124515, -117944, -103729, -72652, -7924};
const long filt_b2[nBand+1] = {62534, 60236, 56351, 50201, 41895, 35460};
