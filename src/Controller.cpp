#include <Controller.h>

static void logError(const std::string& context, const std::exception& e) {
    std::cerr << "Controller❌ " << context << ": " << e.what() << std::endl;
}

Controller::Controller()
{
    std::cout << "Controller connect" << std::endl;
    bookList = db.getLazyBooks();
    std::cout << "Controller connect" << std::endl;
    readerList = db.getLazyReaders();
    std::cout << "Controller connect" << std::endl;
    initializationAdmin();
    std::cout << "Controller connect" << std::endl;
    std::cout << "All ok" << std::endl;
}

void Controller::initializationAdmin()
{
    std::shared_ptr<Admin> admin = getAdmin(1);
    if (!admin)
    {
        admin = std::make_shared<Admin>(1, "Admin", "Admin");
        db.addUser(admin->getId(), admin->getUsername(), admin->getPassHash(), admin->getPassKey(), admin->getRole());
    }
    adminList.push_back(admin);
}

void Controller::refresh()
{
    bookList = db.getLazyBooks();
    readerList = db.getLazyReaders();
}

std::list<LazyReader> Controller::getLazyReaders()
{
    return readerList;
}

std::list<LazyBook> Controller::getLazyBooks()
{
    return bookList;
}

std::list<std::shared_ptr<Book>> Controller::getBooksByUserId(int userId)
{
    auto reader = getReader(userId);
    if (reader)
        return reader->getBookList();
    return std::list<std::shared_ptr<Book>>{nullptr};
}

std::shared_ptr<User> Controller::loginAndGetUser(const std::string& userName, const std::string& pass)
{
    std::shared_ptr<User> user = db.loadUserByName(userName);
    if (user && user->checkPassword(pass))
    {
        return user;
    }
    return nullptr;
}

bool Controller::registrationReader(const std::string& uname, const std::string& pass)
{
    try
    {
        if (db.loadUserByName(uname) != nullptr)
        {
            return false;
        }

        int id = db.getLastIdFromTable("Users", "user_id");
        Reader reader(id + 1, uname, pass);
        db.addUser(id + 1, reader.getUsername(), reader.getPassHash(), reader.getPassKey(), (int)reader.getRole());
        readerList.emplace_back(id + 1, uname);
        refresh();
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
    if (!user || static_cast<Role>(user->getRole()) != Role::ADMIN)
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
    refresh();
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
    refresh();
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
    refresh();
    return true;
}

std::shared_ptr<Reader> Controller::getReader(int readerId)
{
    std::shared_ptr<User> user = db.loadUserById(readerId);
    if (!user || static_cast<Role>(user->getRole()) != Role::READER)
    {
        return nullptr;
    }
    std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(user);
    if (!reader)
    {
        return nullptr;
    }
    return reader;
}

bool Controller::borrowBook(int userId, int bookId)
{
    std::shared_ptr<Reader> reader = getReader(userId);
    std::shared_ptr<Book> book = db.loadBook(bookId);
    if (!reader || !book)
    {
        return false;
    }
    reader->takeBook(book);
    return true;
}

bool Controller::returnBook(int userId, int bookId)
{
    std::shared_ptr<Reader> reader = getReader(userId);
    std::shared_ptr<Book> book = db.loadBook(bookId);
    if (!reader || !book)
    {
        return false;
    }
    reader->returnBook(book);
    return true;
}



