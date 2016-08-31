/*
 * The MIT License (MIT)
 * Copyright (C) 2016 Marco Guerri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 * Software, and to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __TEST_H__
#define __TEST_H__

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN  " \x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define FAIL() printf(ANSI_COLOR_RED "FAILED "ANSI_COLOR_RESET" %s (line %d)\n", __func__, __LINE__)
#define PASSED() printf(ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET" %s \n", __func__);
#define _assert(test) do { if (!(test)) { FAIL(); } else PASSED() } while(0)

#endif
