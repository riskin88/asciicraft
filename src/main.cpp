//
// Created by honza on 01.05.21.
//

#include "CApplication.h"
#include "SCommands.h"

using namespace std;

int main(void) {
    CApplication app(make_shared<CInterface>(cin, cout));
    app.RegisterMenuCommand(SCommands::New())
            .RegisterMenuCommand(SCommands::Load())
            .RegisterMenuCommand(SCommands::Quit(app))

            .RegisterPlayCommand(SCommands::Pause())
            .RegisterPlayCommand(SCommands::Mine())
            .RegisterPlayCommand(SCommands::Build())
            .RegisterPlayCommand(SCommands::Plant())
            .RegisterPlayCommand(SCommands::Eat())

            .RegisterPauseCommand(SCommands::Unpause())
            .RegisterPauseCommand(SCommands::Craft())
            .RegisterPauseCommand(SCommands::Save())
            .RegisterPauseCommand(SCommands::Quit(app));

    try {
        app.Run();
    }
    catch (const std::exception &ex) {
        cerr << ex.what();
        return 1;
    }
    return 0;
}
