using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Collections.Generic;
using UILibrarySystem.Models;

namespace UILibrarySystem.Api.LibraryClient.Api
{
    public class ApiService
    {
        private readonly HttpClient _client;
        private readonly string _baseUrl = "http://localhost:18080"; // адрес сервера

        public ApiService()
        {
            _client = new HttpClient();
        }

        // --- Авторизация ---
        public async Task<LoginResult?> LoginAndGetInfoAsync(string username, string password)
        {
            var data = new { username, password };
            var json = JsonSerializer.Serialize(data);
            var content = new StringContent(json, Encoding.UTF8, "application/json");

            var response = await _client.PostAsync($"{_baseUrl}/login", content);
            if (!response.IsSuccessStatusCode) return null;

            var jsonResult = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<LoginResult>(jsonResult, new JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true
            });
        }

        // --- Регистрация ---
        public async Task<bool> RegisterAsync(string username, string password)
        {
            var data = new { username, password };
            var response = await PostAsync("/register", data);
            return response.IsSuccessStatusCode;
        }

        // --- Получение списка книг ---
        public async Task<List<Book>> GetBooksAsync()
        {
            var response = await _client.GetAsync($"{_baseUrl}/books");
            response.EnsureSuccessStatusCode();
            var json = await response.Content.ReadAsStringAsync();
            var books = JsonSerializer.Deserialize<List<Book>>(json, new JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true
            });
            return books ?? new List<Book>();
        }

        public async Task<List<Book>> GetMyBooksAsync(int userId)
        {
            var data = new { userId };
            var json = JsonSerializer.Serialize(data);
            var content = new StringContent(json, Encoding.UTF8, "application/json");

            var response = await _client.PostAsync($"{_baseUrl}/mybooks", content);
            if (!response.IsSuccessStatusCode) return new List<Book>();

            var jsonResult = await response.Content.ReadAsStringAsync();
            var books = JsonSerializer.Deserialize<List<Book>>(jsonResult, new JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true
            });

            return books ?? new List<Book>();
        }

        // --- Взять книгу ---
        public async Task<bool> BorrowBookAsync(int userId, int bookId)
        {
            var data = new { userId, bookId };
            var response = await PostAsync("/borrow", data);
            return response.IsSuccessStatusCode;
        }

        // --- Вернуть книгу ---
        public async Task<bool> ReturnBookAsync(int userId, int bookId)
        {
            var data = new { userId, bookId };
            var response = await PostAsync("/return", data);
            return response.IsSuccessStatusCode;
        }

        // --- Админ: создать учебник ---
        public async Task<bool> CreateTextbookAsync(int adminId, string title, string author, Subject subject, Level level, string edition)
        {
            var data = new { adminId, title, author, subject = (int)subject, level = (int)level, edition };
            var response = await PostAsync("/admin/book/text", data);
            return response.IsSuccessStatusCode;
        }

        // --- Админ: создать роман ---
        public async Task<bool> CreateNovelAsync(int adminId, string title, string author, Genre genre, int year, int pages)
        {
            var data = new { adminId, title, author, genre = (int)genre, year, pages };
            var response = await PostAsync("/admin/book/novel", data);
            return response.IsSuccessStatusCode;
        }

        // --- Админ: создать научную книгу ---
        public async Task<bool> CreateResearchBookAsync(int adminId, string title, string author, Field field, string conf, string doi)
        {
            var data = new { adminId, title, author, field = (int)field, conf, doi };
            var response = await PostAsync("/admin/book/research", data);
            return response.IsSuccessStatusCode;
        }

        // --- Вспомогательный метод для POST ---
        private async Task<HttpResponseMessage> PostAsync(string route, object data)
        {
            var json = JsonSerializer.Serialize(data);
            var content = new StringContent(json, Encoding.UTF8, "application/json");
            var response = await _client.PostAsync($"{_baseUrl}{route}", content);
            return response;
        }
    }
}
