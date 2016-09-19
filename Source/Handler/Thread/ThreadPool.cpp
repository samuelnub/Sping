/*
This isn't a real implementation file of the threadpool.h, just credit:
From https://github.com/progschj/ThreadPool

Copyright (c) 2012 Jakob Progsch, Václav Zeman

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

/*
Example:

1 #include <iostream>
2 #include <vector>
3 #include <chrono>
4

5 #include "ThreadPool.h"
6

7 int main()
8 {
9
10     ThreadPool pool(4);
11     std::vector< std::future<int> > results;
12

13     for(int i = 0; i < 8; ++i) {
14         results.emplace_back(
15             pool.enqueue([i] {
16                 std::cout << "hello " << i << std::endl;
17                 std::this_thread::sleep_for(std::chrono::seconds(1));
18                 std::cout << "world " << i << std::endl;
19                 return i*i;
20             })
21         );
22     }
23

24     for(auto && result: results)
25         std::cout << result.get() << ' ';
26     std::cout << std::endl;
27
28     return 0;
29 }

*/


// deadpool