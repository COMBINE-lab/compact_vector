#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include <compact_vector.hpp>
#include <misc.hpp>

using namespace std::chrono;

struct timer {
  high_resolution_clock::time_point start;
  timer()
    : start(high_resolution_clock::now())
  { }
};
std::ostream& operator<<(std::ostream& os, timer& t) {
  auto end_time = high_resolution_clock::now();
  os << duration_cast<duration<double>>(end_time - t.start).count();
  t.start = end_time;
  return os;
}


int main(int argc, char *argv[]) {
  auto                    prg  = seeded_prg<std::mt19937_64>();
  static constexpr size_t size = 200000000;
  unsigned bpe=16;
  std::vector<uint16_t> g(size);
  std::uniform_int_distribution<> dis(1, std::numeric_limits<uint16_t>::max());
  {
    compact::vector<uint64_t> v(bpe);
    for (size_t i = 0; i < size; ++i) {
      v.push_back(dis(prg));
      g[i] = v[i];
      //std::cout << v[i] << ", ";
    }
    //std::cout << "\n\n";
    std::ofstream ofile("testfile.bin", std::ios::binary);
    v.serialize(ofile);
    ofile.close();
  }
  {

    std::string s("testfile.bin");
    auto bpe2 = compact::get_bits_per_element(s);
    compact::vector<uint64_t> v(bpe2);
    bool usemmap = (std::string(argv[1]) == "mmap") ? true : false;
    {
      timer t;
      v.deserialize(s, usemmap);
      std::cerr << "de-serialize took : " << t << "\n";
    }
    std::cerr << "v.size() = " << v.size() << "\n";
    for (size_t i = 0; i < v.size(); ++i) {
      if (v[i] != g[i]) {
        std::cerr << "v[" << i << "] = " << v[i] << " but , g[" << i << "] = " << g[i] << "\n";
        return 1;
      }
    }
  }
  return 0;
}
