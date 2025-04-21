#include "ApiServer.h"

ApiServer::ApiServer(int port) : port_(port) {
    setupRoutes();
}

void ApiServer::run() {
    std::cout << "🚀 Server running at http://localhost:" << port_ << std::endl;
    app_.port(port_).multithreaded().run();
}

void ApiServer::setupRoutes() {
    // Регистрация
    CROW_ROUTE(app_, "/register").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body)
                return crow::response(400, "Invalid JSON");

            std::string username = body["username"].s();
            std::string password = body["password"].s();

            bool success = controller_.registrationReader(username, password);
            return success ? crow::response(200, "Registered successfully")
                           : crow::response(409, "Username already exists");
        });

    // Логин
    CROW_ROUTE(app_, "/login").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body)
                return crow::response(400, "Invalid JSON");

            std::string username = body["username"].s();
            std::string password = body["password"].s();

            std::shared_ptr<User> user = controller_.loginAndGetUser(username, password);
            if (user)
            {
                crow::json::wvalue result;
                result["id"] = user->getId();
                result["username"] = user->getUsername();
                result["role"] = user->getRole();
                return crow::response(200, result);
            }

            return crow::response(401, "Invalid credentials");
        });

    // Список книг
    CROW_ROUTE(app_, "/books").methods("GET"_method)
        ([this]() {
            crow::json::wvalue result;
            int i = 0;
            for (auto book : controller_.getLazyBooks()) {
                result[i]["id"] = book.getId();
                result[i]["title"] = book.getTitle();
                ++i;
            }
            return crow::response(result);
        });

    // Книги конкретного пользователя
    CROW_ROUTE(app_, "/mybooks").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("userId"))
                return crow::response(400, "Invalid JSON");

            int userId = body["userId"].i();

            auto books = controller_.getBooksByUserId(userId);
            crow::json::wvalue result;

            int i = 0;
            for (const auto& book : books)
            {
                result[i]["id"] = book->getId();
                result[i]["title"] = book->getTitle();
                result[i]["author"] = book->getAuthor();
                result[i]["bookType"] = book->getTypeBook();
                ++i;
            }

            return crow::response(result);
        });

    // Взять книгу
    CROW_ROUTE(app_, "/borrow").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            int userId = body["userId"].i();
            int bookId = body["bookId"].i();

            bool success = controller_.borrowBook(userId, bookId);
            return success ? crow::response(200, "Book borrowed")
                           : crow::response(400, "Failed to borrow");
        });

    // Вернуть книгу
    CROW_ROUTE(app_, "/return").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            int userId = body["userId"].i();
            int bookId = body["bookId"].i();

            bool success = controller_.returnBook(userId, bookId);
            return success ? crow::response(200, "Book returned")
                           : crow::response(400, "Failed to return");
        });

    // 📘 Создание учебника
    CROW_ROUTE(app_, "/admin/book/text").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body)
                return crow::response(400, "Invalid JSON");

            int adminId = body["adminId"].i();
            std::string title = body["title"].s();
            std::string author = body["author"].s();
            Subject subject = static_cast<Subject>(body["subject"].i());
            Level level = static_cast<Level>(body["level"].i());
            std::string edition = body["edition"].s();

            bool success = controller_.createBookText(adminId, title, author, subject, level, edition);
            return success ? crow::response(200, "Textbook created")
                           : crow::response(403, "Permission denied or error");
        });

    // 📖 Создание романа
    CROW_ROUTE(app_, "/admin/book/novel").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body)
                return crow::response(400, "Invalid JSON");

            int adminId = body["adminId"].i();
            std::string title = body["title"].s();
            std::string author = body["author"].s();
            Genre genre = static_cast<Genre>(body["genre"].i());
            int year = body["year"].i();
            int pages = body["pages"].i();

            bool success = controller_.createBookNovel(adminId, title, author, genre, year, pages);
            return success ? crow::response(200, "Novel created")
                           : crow::response(403, "Permission denied or error");
        });

    // 📚 Создание научной книги
    CROW_ROUTE(app_, "/admin/book/research").methods("POST"_method)
        ([this](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body)
                return crow::response(400, "Invalid JSON");

            int adminId = body["adminId"].i();
            std::string title = body["title"].s();
            std::string author = body["author"].s();
            Field field = static_cast<Field>(body["field"].i());
            std::string conf = body["conf"].s();
            std::string doi = body["doi"].s();

            bool success = controller_.createBookResearch(adminId, title, author, field, conf, doi);
            return success ? crow::response(200, "Research book created")
                           : crow::response(403, "Permission denied or error");
        });
}
