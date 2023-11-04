
void cool() {}

void hello(...) {
  [[clang::musttail]] return cool();
}

typedef void(*ooo)(...);
int main() {
  ooo a = (void*)&hello;
  a(1, 2, 3, 4);
  
}
