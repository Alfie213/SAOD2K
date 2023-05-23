using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;


namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        {
            string str = " фыидо, fjbld33- 2олт?";
            Console.WriteLine(str);

            //Regex re = new Regex(@"(\w)\1");
            //re = new Regex(@"(\W*)(\w+)(\W+)(\w+)(\W+)(\w+)(\W*)");
            //Console.WriteLine(re.Replace(str, "$1$4$3$2$5$6$7"));
            //Regex re = new Regex(@"\w*\d\w*");// At least 1 number.
            //Regex re = new Regex(@"\b\w*(\w)\1\w*\b"); // Doubled symbols.
            //Regex re = new Regex(@"\b[A-Za-z0-9]+\b"); // Only Latin symbols and numbers.
            Regex re = new Regex(@"\b\w*[A-Za-z]\w*\b"); // At least 1 Latin symbol.
            MatchCollection mc = re.Matches(str);
            foreach (var m in mc)
                Console.WriteLine(m);

            //Console.Read();

            //string orig;
            //try
            //{
            //    using (StreamReader sr = new StreamReader("Dictionary.xml"))
            //    {
            //        orig = sr.ReadToEnd();
            //        Console.WriteLine(orig.Length);
            //        //Regex regex = new Regex(@"<[a-zA-Z]+[^>]*>([^<]+)<\/[a-zA-Z]+>"); // Все листовые теги, т.е. теги, в которых нет других тегов, а содержится только текст.
            //        Regex regex = new Regex(@"</main-word>(\s*)([а-яА-Яa-zA-Z\u0301\-]+)");
            //        MatchCollection mcс = regex.Matches(orig);
            //        foreach (var m in mcс)
            //            Console.WriteLine(m);
            //    }

            //}
            //catch (Exception ex)
            //{
            //    Console.WriteLine("Ошибка чтения файла: \"Dictionary.xml\"\n{0}", ex);
            //    return;
            //}

            // Загрузка файла Dictionary.xml в XmlDocument
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("Dictionary.xml");

            // Получение списка всех main-word
            XmlNodeList mainWordNodes = xmlDoc.SelectNodes("//main-word");

            // Исправление каждого main-word, если необходимо
            foreach (XmlNode mainWordNode in mainWordNodes)
            {
                // Если слово стоит за пустым main-word
                if (string.IsNullOrWhiteSpace(mainWordNode.InnerText))
                {
                    // Получение текста слова
                    string word = mainWordNode.NextSibling.InnerText.Trim();

                    // Удаление пустого main-word
                    mainWordNode.ParentNode.RemoveChild(mainWordNode);

                    // Получение первой буквы слова
                    string firstLetter = word.Substring(0, 1).ToUpper();

                    // Поиск первого элемента с нужной буквой
                    XmlNode firstLetterNode = xmlDoc.SelectSingleNode("//letter[bold='" + firstLetter + "']");
                    XmlElement boldElement;

                    if (firstLetterNode == null)
                    {
                        // Создание нового элемента letter с нужной буквой
                        firstLetterNode = xmlDoc.CreateElement("letter");
                        boldElement = xmlDoc.CreateElement("bold");
                        boldElement.InnerText = firstLetter;
                        firstLetterNode.AppendChild(boldElement);
                        xmlDoc.DocumentElement.AppendChild(firstLetterNode);
                    }

                    // Создание нового элемента main-word
                    XmlElement mainWordElement = xmlDoc.CreateElement("main-word");
                    boldElement = xmlDoc.CreateElement("bold");
                    boldElement.InnerText = word;
                    mainWordElement.AppendChild(boldElement);

                    // Получение элемента article
                    XmlNode articleNode = mainWordNode.NextSibling;
                    if (articleNode != null && articleNode.Name == "article")
                    {
                        // Перемещение элемента article в новый main-word
                        articleNode = mainWordNode.NextSibling;
                        mainWordElement.AppendChild(articleNode);
                    }

                    // Добавление нового main-word в нужный элемент letter
                    firstLetterNode.AppendChild(mainWordElement);
                }
            }

            // Сохранение исправленного файла
            xmlDoc.Save("Dictionary.xml");
            Console.WriteLine("end");

            Console.Read();
        }
    }
}
