/*
 * Copyright (c) 2019-present Bowser65 & vinceh121, All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "coffeepot.hpp"

#include <stdexcept>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream> //XXX: eclipse removes this one at optimization

bool quiet = false;

bool is_file_powdder(char *file) {
    std::ifstream in(file);
    int fin = ((in.get() & 0xFF) << 16) | ((in.get() & 0xFF) << 8) | in.get();
    return fin == POWDDER_MAGIC_NUMBER;
}

void _vm_info(const std::string &text) {
    if (quiet) return;
    std::cout << text << std::endl;
}

void _vm_err(const std::string &text) {
    if (quiet) return;
    std::cerr << text << std::endl;
}

CoffeePot::CoffeePot() {

}

bool CoffeePot::is_started() {
    return started;
}

void CoffeePot::start(char *inFile) {
    if (started) {
        throw std::runtime_error("Tried to start a VM that is already started");
    }
    started = true;

}

void print_license() {
    std::cout
            << "Copyright (c) 2019-present Bowser65 & vinceh121, All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
            << std::endl;
}

void print_help() {
    std::cout << "CoffePot VM v" << COFFEE_POT_VERSION << std::endl;
    std::cout << "coffeepot [options] CUP_FILE" << std::endl;
    std::cout << "-- General Options" << std::endl;
    std::cout << "\t-q, --quiet\tPrevents the VM from printing to stdout and stderr. Program will still output."
              << std::endl;
    std::cout << "-- About CoffeePot" << std::endl;
    std::cout << "\t-h, --help\tShows this help page." << std::endl;
    std::cout << "\t-v, --version\tPrints version information and exits." << std::endl;
    std::cout << "\t--license\tPrints the program's license and exists." << std::endl;
    std::exit(0);
}

void unknown_arg(char *arg) {
    _vm_err("Unknown argument \"" + std::string(arg) + "\"");
    std::exit(-1);
}

int main(int argc, char **argv) {
    // std::cout << __cplusplus << std::endl;
    if (argc <= 1)
        print_help();
    CoffeePot *cof = new CoffeePot();

    if (argc > 2) {
        for (int i = 1; i < argc - 1; i++) { // Do not read the last argument here as it is the .cup file
            if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
                print_help();
            } else if (strcmp("--version", argv[i]) == 0 || strcmp("-v", argv[i]) == 0) {
                std::cout << "CoffePot VM v" << COFFEE_POT_VERSION << std::endl;
                std::exit(0);
            } else if (strcmp("--license", argv[i]) == 0) {
                print_license();
                std::exit(0);
            } else if (strcmp("--quiet", argv[i]) == 0 || strcmp("-q", argv[i]) == 0) {
                quiet = true;
            } else {
                unknown_arg(argv[i]);
            }
        }
    }

    cof->start(argv[argc - 1]);
    return 0;
}
