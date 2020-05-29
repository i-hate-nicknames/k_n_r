// functions like isupper, isspace, etc can be implemented to either save
// space or time.

// to save space, just check that the value is within range 
int isupper_save_space(char c) {
  return (c >= 'A' && c <= 'Z');
}

// to save time, precompute tables for every function, and then
// just consult the tables at runtime

int IS_UPPER[255] = {0, 0, 0, 0, /* until 'A'*/, 1, 1, 1, /* until 'Z' */, 0, 0, 0};

int isupper_save_time(char c) {
  return IS_UPPER[c];
}
