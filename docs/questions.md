# Как задавать вопросы, чтобы получать от них максимум пользы

## Зачем читать этот текст 

Когда вы решаете задачи или изучаете материал курса, у вас закономерно возникают вопросы. 

Чем лучше вы сформулируете их, тем меньше ассистент/семинарист/лектор потратит времени на его понимание &mdash; 
тем быстрее вы получите ответ.

Этот текст &mdash;  набор рекомендаций, а никак не строгих правил. Если у вас есть вопрос &mdash; смело задавайте его! Тут лишь описаны некоторые практические подходы, чтобы облегчить вам и нам жизнь. 


## У меня вопрос! Что мне делать?!

Хороший подход &mdash; дать себе пару минут осмыслить все происходящее. Иногда бывает ощущение, что "ничего вообще непонятно" &mdash; постарайтесь от него избавиться и понять, что именно вызывает сложности.  Посмотрим на самые часто задаваемые виды вопросов. 

### Вопросы по условию

Хороший подход &mdash; опереться на те части условия, которые вам понятны. Попробуйте додумать ту часть, которая непонятна &mdash; часто интуитивная догадка является правильной. Конечно, **лучше спросить, верно ли вы все поняли, чем потратить много времени, решая другую задачу**.

Бывает, что какая-то часть условия непонятна, потому что плохо сформулирована. 
Если у вас есть вопрос, то скорее всего он возникает не только у вас, поэтому мы можем отредактировать условия, чтобы вашим однокурсникам и будущим поколениям задачи были понятнее. Задавайте вопросы)

### Не компилируется код 

Сообщения об ошибках в плюсах не всегда легко читать, однако почти всегда можно найти подсказки, что же идет не так:

 - Смотрите сначала на самую первую ошибку, которую выдал компилятор, и попытайтесь ее перевести. 
 Даже если не знаете всех слов, просто замена их всех на русские помогает понять, о чем речь. 
 Когда исправите ее &mdash; перекомпилируйте код, и снова исправляйте самую первую. 

 -  Copy-paste ошибки в гугл с большой вероятностью переносит вас на stackoverflow, где кто-то уже столкнулся с подобной проблемой, и ответ можно получить за секунду в первом же комментарии с этого сайтика. 

 - Если все это не помогло, то бывает полезно найти самый короткий код, который выдает такую ошибку компиляции. 
 Попробуйте в отдельном файлике его реализовать &mdash; это поможет избавиться от лишних деталей, и, возможно, сразу поймете в чем проблема.

 - Понятно, что такой код не пройдет тесты, тем не менее делиться им с ассистентом/семинаристом удобнее всего именно через посылку. Сделайте submit, и прикрепите ссылку. Штрафов за посылки у нас нет, но так просто удобнее. Или можете использовать минимально-неработающий код из предыдущего пункта)

 - При реализации решения иногда хочется узнать, будет ли работать какой-то код. Полезно в этом случае заходить на сайт [godbolt](https://godbolt.org/) или [online c++ compiler](https://www.onlinegdb.com/online_c++_compiler), чтобы быстро написать вашу идею, попробовать скомпилировать, получить кучу ошибок, исправить их, и перенести идею в ваше решение. Если вы вдруг не понимаете, почему одна версия работает, а другая нет - это можно смело спрашивать в чате) Но будьте осторожны, не проспойлерите ваше решение. Если не выходит оформить в виде абстрактного вопроса по плюсам - приходите к преподам или ассистам)


### Не проходят тесты 

 - Убедитесь, что вы прогнали тесты с санитайзерами. Как это делать было описано в [условии задачи multiplication](/tasks/intro/multiplication) &mdash; в последней секции условия. Так вы сможете отловить проблемы с памятью локально, и решать их будет удобнее. 

 - Если используете CLion &mdash; встроенный дебаггер очень удобен, чтобы построчно проходить и понимать, что в задаче идет не так. А если вы фанат gdb в консоли или не знаете как настроить дебаггер в вашей IDE &mdash; можете уже сейчас тренироваться, на АКОСе пригодится)) Чтобы запустить код под gdb:
    ```cpp
    // in folder build/ 
    make test_task
    gdb ./test_task
    ```
    [Базовые команды](https://condor.depaul.edu/glancast/373class/docs/gdb.html), также можете глянуть [лекцию по нему прошлого года](https://www.youtube.com/watch?v=UCSAumkhBV0&list=PLEwK9wdS5g0psb_ZYjskVmPBQfEJfI9ui&index=6).

 - Можно найти первый тест, на котором у вас валится программа (если по выводу на консоль это не очень понятно). Просто закомментрируйте часть и попробуйте запустить программу. Когда вы поймете, в какой именно ситуации у вас возникают проблемы, можете прогнать ваш алгоритм руками. И если не получается - в своем вопросе добавьте этот тест.
## Общие вещи 

- Если ваш вопрос можно задать ассистенту &mdash; лучше именно так и делать, это наша основаная обязанность) Но, конечно, спрашивать семинаристов или лектора не запрещается.

- используйте **ссылки** в своих собщениях на те материалы, которыми пользуетесь.

    Если это условие задачи &mdash; прикрепите на него ссылку, чтобы можно было мгновенно перейти и сразу начать смотреть. 
    
    Если это вопрос по плюсам &mdash; скиньте страничку cppreference, которую вы смотрите. 
    
    Если это посылка &mdash; сразу скидывайте ссылку на джобу проверки.
    
    Если нужно посмотреть в ваш код - ссылку на файл с решением в gitlab-е (в браузере перейдите на ветку _submit/task_name_ и там можно будет его найти) или воспользуйтесь сайтом [pastebin](https://pastebin.com/).

    Все это сделает ваш вопрос более привлекательным к рассмотрению :) 

-  Круто и удобно, когда в начале вопроса кратко описана его суть, а потом уже идут все детали. 
Тогда можно сразу понять, о чем в целом идет речь. 
    
    А еще приятно, когда весь вопрос написан в одном сообщении &mdash; нет дудоса уведомлениями. То же можно сказать про общий чат: лучше отредактировать предыдущее сообщение, чем написать новое с поправками - это добавляет порядка в дискуссию. 

- Если вы уже долго пытаетесь решить проблему, но ничего не получается, смело идите с любыми вопросами к ассистентам! 
Будет круто, если вы кратко опишите ваш прогресс, типо "я пытался сделать вот так..., у меня не получилось(". 
Попробуйте сами установить себе порог, который кажется вам разумным, после которого вы идете за помощью в любом случае. 
Учиться решать вопросы самостоятельно, безусловно, полезно, но страдания при поиске не должны быть слишком мучительными. 
**Разобраться в вопросе с помощью всегда гарантированно лучше, чем забить и не разбираться вовсе.**

- Есть тонкая грань между задаванием вопросов (особенно одногруппникам) и списыванием, которое запрещено на нашем курсе. Давайте все вместе ее ощущать и не переступать. Чтобы вам было проще наладить ментальную связь со всеми:
    - Можно в общий чат
        - Если вопрос можно оформить в виде абстрактного вопроса по плюсам
        - Вопросы по условию, по интерфейсу функций
        - Падаеет job-a и не знаете кому написать &mdash; ответит любой свободный человек
        - Еще можно попробовать в нем поискать по ключевым словам &mdash; вдруг ваш вопрос уже кто-то недавно задавал
    - В личные сообщения преподавателям и ассистам
        - Если нужно зашарить кусок вашего кода
        - Вопрос, почему ваша реализация не работает
    - Остальное на ваше усмотрение - может ли вопрос проспойлерить ваше решение или нет, стесняетесь ли писать в общий чат или может у вас есть любимый ассист

## Когда вам быстрее всего ответят 

Не бойтесь писать в общий чат (или ваши групповые чаты), там обычно отвечают быстрее всего, а если ассисты заняты &mdash; однокурсники придут вам на помощь.

Самый большой поток вопросов обычно бывает непосредственно перед дедлайном по домашке. Соответственно, сложно сразу ответить всем. Если вы сядете за нее немного заранее, будет проще вам помогать)

Если вы понимаете, что ответ преподов не помогает вам решить проблему, попробуйте переформулировать вопроc и сделать его более конкретным. Бывали случаи, когда преподаватели не могли просто распарсить вопрос на русском языке :)

А еще, когда наступает ночь, лектор, семинаристы и ассисты засыпают...