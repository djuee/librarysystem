#include <LazyReader.h>
#include <iostream>
#include <DatabaseManager.h>

LazyReader::LazyReader(int id, std::string uname)
    : m_id(id), m_uname(uname)
{
    update();
};

int LazyReader::getId() const
{
    return m_id;
}

std::string LazyReader::getUname() const
{
    return m_uname;
}

std::list<std::shared_ptr<LazyBook>> LazyReader::getBookList() const
{
    return m_bookList;
}

void LazyReader::update()
{
    try {
        DatabaseManager& db = DatabaseManager::getInstance();

        m_bookList = db.getLazyBooksByUserId(m_id);
    } catch (const std::exception& e) {
        std::cerr << "❌ LazyReader::update(): ошибка при обновлении книг: " << e.what() << std::endl;
    }
}

std::shared_ptr<Reader> LazyReader::loadReader()
{
    if (isLoaded()) {
        return m_loadedReader;
    }

    m_loadedReader = std::dynamic_pointer_cast<Reader>(
        DatabaseManager::getInstance().loadUserById(m_id)
        );

    if (!m_loadedReader) {
        std::cerr << "❌ LazyReader::loadReader(): Не удалось загрузить Reader с ID " << m_id << std::endl;
    }

    return m_loadedReader;
}

bool LazyReader::isLoaded() const
{
    return m_loadedReader != nullptr;
}

void LazyReader::freeReader()
{
    m_loadedReader.reset();
}
