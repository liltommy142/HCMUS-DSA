#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// Hàm chuẩn hóa đoạn văn
void normalizeParagraph(const char *paragraph, char *normalized)
{
    int n = strlen(paragraph);
    int j = 0;
    bool spaceNeeded = false;

    for (int i = 0; i < n; ++i)
    {
        char c = paragraph[i];

        if (isspace(c))
        {
            spaceNeeded = true; // Đánh dấu cần khoảng trắng
        }
        else
        {
            if (ispunct(c))
            {
                if (j > 0 && normalized[j - 1] == ' ')
                {
                    j--; // Xóa khoảng trắng thừa trước dấu câu
                }
                normalized[j++] = c;
                spaceNeeded = true; // Đánh dấu cần khoảng trắng
            }
            else
            {
                if (spaceNeeded && j > 0)
                {
                    normalized[j++] = ' '; // Thêm khoảng trắng
                }
                normalized[j++] = c;
                spaceNeeded = false; // Không cần khoảng trắng
            }
        }
    }
    normalized[j] = '\0'; // Kết thúc chuỗi chuẩn hóa
}

// Hàm đếm số từ trong đoạn văn
int countWords(const char *paragraph)
{
    int count = 0;
    bool inWord = false;

    for (int i = 0; paragraph[i] != '\0'; ++i)
    {
        if (isspace(paragraph[i]))
        {
            inWord = false; // Không ở trong từ
        }
        else if (!inWord)
        {
            inWord = true; // Bắt đầu một từ mới
            count++;       // Tăng số đếm từ
        }
    }

    return count; // Trả về số từ
}

// Hàm tìm từ dài nhất trong đoạn văn
void findLongestWord(const char *paragraph, char *longestWord)
{
    int maxLength = 0;
    int currentLength = 0;
    const char *start = nullptr;
    const char *wordStart = nullptr;

    for (int i = 0;; ++i)
    {
        char c = paragraph[i];
        if (isalnum(c))
        {
            if (!start)
            {
                start = &paragraph[i]; // Bắt đầu một từ mới
            }
            currentLength++; // Tăng độ dài từ hiện tại
        }
        else
        {
            if (currentLength > maxLength)
            {
                maxLength = currentLength; // Cập nhật độ dài từ dài nhất
                strncpy(longestWord, start, currentLength);
                longestWord[currentLength] = '\0'; // Kết thúc chuỗi từ dài nhất
            }
            currentLength = 0; // Đặt lại độ dài từ hiện tại
            start = nullptr;   // Đặt lại điểm bắt đầu từ
        }

        if (c == '\0')
            break; // Kết thúc đoạn văn
    }
}

int main()
{
    const int MAX_LEN = 1000;
    char paragraph[MAX_LEN];
    char normalized[MAX_LEN];
    char longestWord[MAX_LEN];

    // Nhập đoạn văn
    cout << "Enter a paragraph: ";
    cin.getline(paragraph, MAX_LEN);

    // Chuẩn hóa đoạn văn
    normalizeParagraph(paragraph, normalized);

    // Đếm số từ
    int wordCount = countWords(normalized);

    // Tìm từ dài nhất
    findLongestWord(normalized, longestWord);

    // Xuất kết quả
    cout << "Normalized paragraph:\n"
         << normalized << endl;
    cout << "Word count: " << wordCount << endl;
    cout << "Longest word: " << longestWord << endl;

    return 0; // Kết thúc chương trình
}