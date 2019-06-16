#include <vector>
#include "Allocator.h"
int main(){
    std::allocator<int> a1;
    a1.allocate();
    Allocator a2;
}