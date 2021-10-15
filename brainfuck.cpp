#include <iostream>
#include <span>
#include "brainfuck.h"

namespace brainfuck {

    executor::executor(std::vector<instr>&& ins, size_t store_size)
            : ins(std::move(ins))
            , store(store_size)
            , store_idx(store_size / 2) {}

    executor::executor(std::string& ins, size_t store_size)
            : ins(ins)
            , store(store_size)
            , store_idx(store_size / 2) {}

    bool executor::step() {
        switch (ins.current()) {
            case instr::left:
                store_idx -= 1;
                break;
            case instr::right:
                store_idx += 1;
                break;
            case instr::inc:
                current_int() += 1;
                break;
            case instr::dec:
                current_int() -= 1;
                break;
            case instr::read: {
                Int input = 0;
                std::cin >> input;
                current_int() = input;
            } break;
            case instr::print:
                std::cout << current_int() << std::endl;
                break;
            case instr::loop_start:
                if (current_int() == 0) {
                    ins.go_to_matching();
                }
                break;
            case instr::loop_end:
                if (current_int() != 0) {
                    ins.go_to_matching();
                }
                break;
        }

        auto ok = ins.next();
        return ok;
    }

    void executor::run() {
        while (step());
    }

    Int& executor::current_int() {
        return store.at(store_idx);
    }

    instrs::instrs(std::vector<instr>&& ins) : data(ins) {
        if (!data_is_valid())
            throw std::runtime_error("Invalid data");
    }

    instrs::instrs(std::string& ins) {
        std::vector<instr> v;
        v.reserve(ins.size());
        for (auto c : ins) {
            if (c == '<') {
                v.push_back(instr::left);
            } else if (c == '>') {
                v.push_back(instr::right);
            } else if (c == '+') {
                v.push_back(instr::inc);
            } else if (c == '-') {
                v.push_back(instr::dec);
            } else if (c == 'p') {
                v.push_back(instr::print);
            } else if (c == 'r') {
                v.push_back(instr::read);
            } else if (c == '[') {
                v.push_back(instr::loop_start);
            } else if (c == ']') {
                v.push_back(instr::loop_end);
            } else {
                throw std::runtime_error("Invalid character.");
            }
        }
        std::swap(data, v);
    }

    bool instrs::data_is_valid() const noexcept {
        int32_t counter = 0;
        for (auto item : data) {
            if (item == instr::loop_start)
                ++counter;
            if (item == instr::loop_end)
                --counter;
            if (counter < 0)
                return false;
        }
        return counter == 0;
    }

    instr instrs::current() const noexcept {
        return data[cursor];
    }

    bool instrs::next() noexcept {
        size_t new_cursor = cursor + 1;
        if (new_cursor < data.size()) {
            cursor = new_cursor;
            return true;
        } else {
            return false;
        }
    }

    void instrs::go_to_matching() {
        auto start = data[cursor];

        if (start == instr::loop_start) {

            int32_t count = 0;
            for (size_t i = cursor + 1; i < data.size(); ++i) {
                auto instr = data[i];
                if (instr == instr::loop_start)
                    count += 1;
                if (instr == instr::loop_end)
                    count -= 1;
                if (count < 0) {
                    cursor = i;
                    break;
                }
            }

        } else if (start == instr::loop_end) {

            int32_t count = 0;
            for (ssize_t i = cursor - 1; i >= 0; --i) {
                auto instr = data[i];
                if (instr == instr::loop_start)
                    count -= 1;
                if (instr == instr::loop_end)
                    count += 1;
                if (count < 0) {
                    cursor = i;
                    break;
                }
            }

        } else {
            throw std::runtime_error("Trying to go from a bad place.");
        }
    }

}