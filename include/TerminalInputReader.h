/**
 * @file TerminalInputReader.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#ifndef TERMINAL_INPUT_READER_H
#define TERMINAL_INPUT_READER_H

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdexcept>

#include "InputReader.h"
#include "InputDelegate.h"
#include "Singleton.h"

#define INPUT_READER_TIMEOUT_MICROS (100)
#define INPUT_READER_TIMEOUT_SECONDS (0)


namespace monsterbattle
{
    class TerminalInputReader: 
        public InputReader,
        public Singleton<TerminalInputReader>
    {
        friend Singleton;

        public:
        static constexpr struct timeval Timeout = {.tv_sec=INPUT_READER_TIMEOUT_SECONDS, .tv_usec=INPUT_READER_TIMEOUT_MICROS};

        TerminalInputReader(const TerminalInputReader& other) = delete;
        ~TerminalInputReader() noexcept;

        void update() override;

        private:

        struct termios newAttributes;
        struct termios oldAttributes;

        TerminalInputReader();
    };
}

#endif