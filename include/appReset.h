#pragma once

class AppReset
{
    private:
        const char* DATABASE_FILE_DIR = "database/things_list.db";
    public:
        AppReset();
        ~AppReset();

        int resetApplication();
        int startApplication();
};

