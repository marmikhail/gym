# gym
Курсовая работа

Пользовательская документация----------------------------------------------------------------

После запуска пользователь попадает в форму проверки прав пользователя

От пользователя требуется ввести логин и пароль. После входа пользователь попадает в основное приложение на главную страницу с информацией. 

Здесь пользователь видит последние 10 записей по спортзалу, в котором он работает. Так же он может добавлять записи в форме, расположенной в правом нижнем углу. После нажатия кнопки “Добавить”, новость будет опубликована на стене. Дата записи добавляется автоматически.

Далее пользователь может открыть меню. Где раздел “Главная” – это главная страница приложения, а раздел “Абонементы” – режим работы с абонементами. Нажав на элемент “Абонементы”, пользователь переходит в режим добавления абонементов.

В данном режиме пользователь может найти все абонементы, оформленные в его спортзале.  В данном режиме доступен поиск клиента по фамилии, добавление/изменение/удаление абонемента, просмотр информации.

Введя в данное поле фамилию клиента и нажав на кнопку поиска, пользователь может найти абонементы клиентов с данной фамилией (ФИО могут повторяться). Так же если пользователь оставит поле пустым и нажмет на кнопку поиска, в таблицу выведутся данные по всем абонементам, оформленным в данном зале. После нажатия на кнопку, поле очищается. 

Справа пользователь может добавить клиента. Здесь он вводит ФИО(полностью),  длительность абонемента (кол-во месяцев) и может выбрать тариф  из выпадающего списка.
Важно, что все поля должны быть заполнены. Далее пользователь нажимает кнопку добавления и в списке слева появляется новый абонемент. Данные о зале и дате приобретения абонемента заполняются автоматически.

В таблице слева пользователь может посмотреть информацию об абонементах, купленных в зале, в котором он работает. Здесь выводятся поля:

•	ID абонемента;
•	ФИО клиента;
•	Приобретенный тариф;
•	Дата приобретения;
•	Срок действия абонемента;
•	Дата окончания действия абонемента.

При двойном нажатии на строку таблицы открывается режим изменения/удаления абонемента. Кнопка “Добавить” меняется на кнопки “Изменить” и “Удалить”. А в правом верхнем углу появляется кнопка “Добавить абонемент” для возврата в режим добавления абонемента. Так же в поля переносится информация о данном абонементе.

В данном режиме пользователь может изменить информацию об абонементе, тогда при нажатии на кнопку “Изменить”, данные в таблице обновятся (дата приобретения останется прежней). Важно, что поля так же не должны быть пустыми. 

Так же в данном режиме пользователь может удалить выбранный абонемент из системы. Для этого он должен нажать на кнопку удаления. При нажатии на кнопку пользователю будет предложено подтвердить свое действие.

Пользователь может вернуться в режим добавления абонемента нажав на кнопку “Добавить абонемент”, либо вернуться на главный экран, выбрав в меню сверху элемент “Главная”.

Инструкция по сборке-----------------------------------------------------------------
Чтобы установить и протестировать приложение необходимо клонировать удаленный репозиторий (https://github.com/marmikhail/gym).
Далее в текстовом файле CMakeLists.txt нужно сделать небольшие изменения.
1.	В set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/msvc2015_64) нужно поменять “C:/Qt/5.15.2/msvc2015_64” на тот путь к Qt5, который на вашем компьютере.
2.	Нужно написать set(CMAKE_INSTALL_PREFIX <адрес, куда устанавливать >) Однако это можно задать в Cmake gui.
Далее необходимо собрать проект в Cmake


Далее необходимо найти в сгенерированных файлах цель INSTALL и назначить ее в качестве запускаемого проекта.

Далее здесь же необходимо собрать данный проект.

После этого программа будет установлена в той папке, которую была прописана выше.
В этой папке нужно открыть папке “bin”, и внутри него лежит файл, запускающий программу – “gym.exe”. 

Учетные данные пользователя для теста:

•	Имя пользователя: Мышкин ИВ
•	Пароль: 1234
