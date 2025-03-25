#include <Controller.h>

static void logError(const std::string& context, const std::exception& e) {
    std::cerr << "Controller❌ " << context << ": " << e.what() << std::endl;
}

Controller::Controller()
{
    bookList = db.getLazyBooks();
    readerList = db.getLazyReaders();
}

void Controller::refresh()
{
    bookList = db.getLazyBooks();
    readerList = db.getLazyReaders();
}

bool Controller::registrationReader(const std::string& uname, const std::string& pass)
{
    try
    {
        if (db.loadUserByName(uname) != nullptr)
        {
            return false;
        }

        int id = db.getLastIdFromTable("Users");
        Reader reader(id + 1, uname, pass);
        db.addUser(id + 1, reader.getUsername(), reader.getPassHash(), reader.getPassKey(), (int)reader.getRole());
        readerList.emplace_back(id + 1, uname);

        return true;
    }
    catch (const std::exception& e)
    {
        logError("registrationReader", e);
        return false;
    }
}

bool Controller::loginUser(const std::string &userName, const std::string &pass)
{
    std::shared_ptr<User> user = db.loadUserByName(userName);
    if (user != nullptr && user->checkPassword(pass))
    {
        return true;
    }
    return false;
}

std::shared_ptr<Admin> Controller::getAdmin(int adminId)
{
    std::shared_ptr<User> user = db.loadUserById(adminId);
    if (user->getRole() != Role::ADMIN)
    {
        return nullptr;
    }
    std::shared_ptr<Admin> admin = std::dynamic_pointer_cast<Admin>(user);
    if (!admin)
    {
        return nullptr;
    }
    return admin;
}

bool Controller::createBookText(int adminId, const std::string& title, const std::string& author,
                    Subject subject, Level level, const std::string& edition)
{
    std::shared_ptr<Admin> admin = getAdmin(adminId);
    if (!admin)
    {
        return false;
    }

    int newId = db.getLastIdFromTable("Books", "id") + 1;
    admin->createBook(newId, title, author, subject, level, edition);
    return true;
}

bool Controller::createBookNovel(int adminId, const std::string& title, const std::string& author,
                     Genre genre, int year, int pages)
{
    std::shared_ptr<Admin> admin = getAdmin(adminId);
    if (!admin)
    {
        return false;
    }

    int newId = db.getLastIdFromTable("Books", "id") + 1;
    admin->createBook(newId, title, author, genre, year, pages);
    return true;
}

bool Controller::createBookResearch(int adminId, const std::string& title, const std::string& author,
                        Field field, const std::string& conf, const std::string& doi)
{
    std::shared_ptr<Admin> admin = getAdmin(adminId);
    if (!admin)
    {
        return false;
    }

    int newId = db.getLastIdFromTable("Books", "id") + 1;
    admin->createBook(newId, title, author, field, conf, doi);
    return true;
}

