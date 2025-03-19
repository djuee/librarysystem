#include <Controller.h>

Controller::Controller()
{
    bookList = db.getLazyBooks();
    readerList = db.getLazyReaders();
}

bool Controller::registrationReader(std::string uname, std::string pass)
{
    try
    {
        int id = db.getLastIdFromTable("Users");
        Reader reader(id+1, uname, pass);
        db.addUser(id+1, reader.getUsername(), reader.getPassHash(), reader.getPassKey(), (int)reader.getRole());
        readerList.emplace_back(id+1, uname);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Controller: Ошибка при создании Читателя" << e.what() << std::endl;
        return false;
    }
}

bool Controller::loginUser(std::string userName, std::string pass)
{
    std::shared_ptr<User> user = db.loadUserByName(userName);
    if (user != nullptr & user->checkPassword(pass))
    {
        return true;
    }
    return false;
}



