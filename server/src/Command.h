/**-*-C++-*-
 * \file
 * \author Guillaume Papin <guillaume.papin@epitech.eu>
 *
 * This file is distributed under the GNU General Public License. See
 * COPYING for details.
 *
 */

#ifndef IRONY_MODE_SERVER_COMMAND_H_
#define IRONY_MODE_SERVER_COMMAND_H_

#include <clang-c/Index.h>

#include "support/TemporaryFile.h"

#include <iosfwd>
#include <string>
#include <vector>

class TemporaryFile;

struct Command {
  Command() {
    clear();
  }

  void clear() {
    action = Unknown;
    flags.clear();
    file.clear();
    line = 0;
    column = 0;
    unsavedFiles.clear();
    cxUnsavedFiles.clear();
  }

#define X(sym, str, desc) sym,
  enum Action {
#include "Commands.def"
  } action;

  std::vector<std::string> flags;
  std::string file;
  unsigned line;
  unsigned column;
  // pair of (filename, content)
  std::vector<std::pair<std::string, std::vector<char>>> unsavedFiles;
  std::vector<CXUnsavedFile> cxUnsavedFiles;
};

std::ostream &operator<<(std::ostream &os, const Command::Action &action);
std::ostream &operator<<(std::ostream &os, const Command &command);

class CommandParser {
public:
  CommandParser();

  Command *parse(const std::vector<std::string> &argv);

private:
  Command command_;
  TemporaryFile tempFile_;
};

#endif // IRONY_MODE_SERVER_COMMAND_H_