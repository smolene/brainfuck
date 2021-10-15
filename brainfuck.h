#pragma once

#include <vector>
#include <optional>
#include <ranges>

namespace brainfuck {
    using Int = int32_t;

    enum class instr {
        left,
        right,
        inc,
        dec,
        read,
        print,
        loop_start,
        loop_end,
    };

    class instrs {
    public:
        explicit instrs(std::vector<instr>&& ins);
        explicit instrs(std::string& ins);
        [[nodiscard]] instr current() const noexcept;
        [[nodiscard]] bool next() noexcept;
        void go_to_matching();

    private:
        std::vector<instr> data;
        size_t cursor{};

        [[nodiscard]] bool data_is_valid() const noexcept;
    };

    class executor {
    public:
        explicit executor(std::vector<instr>&& ins, size_t store_size);
        explicit executor(std::string& ins, size_t store_size);
        bool step();
        void run();

    private:
        instrs ins;
        std::vector<Int> store;
        size_t store_idx{};

        Int& current_int();
    };
}
