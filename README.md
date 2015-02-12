The Chronicles Of Andaria
==================

## About the project

The Chronicles Of Andaria is an implementation of an innovative RPG board game.
> To learn more go to [project wiki].

## Contributing

You can contribute to this project in one of three ways:

1. Browse issues, comment on proposals, report bugs.
2. Clone the project repo, make some changes according to
   development guidelines and issue a pull-request with your changes.
3. Share your opinions and ideas about game.
   For example you can send me an email at <rsoszynski121@gmail.com>.

Not sure where to start? Look for issues listed at [project wiki].
These tasks do not always require a profound insight in the source code,
so I guess that you will find something for yourself.

## Github guidelines

Simply use _Fork & Pull Model_

1. [Fork] this repo.
2. Write your code and push it to your repo.
3. Create a new [pull request].

Remember to mark your contribution by inserting **one** of the lines below into the file license.
> Copyright (C) [modification year] [name and surname] [< e-mail >]
> Thanks to [modification year] [name and surname][< e-mail >]

## Coding style


### Code marks
- **TODO** - Places to fill later with needed code.
- **FIXME** - Places with quick fix to make sth else work, but will probably cause problems if thoroughly used.
- **WARNING** - Places with assumptions not 100% clear.
- **NOTE** - Additional developer notes.
- **BUG** - Bug spotted, marked for grep later on.

### Lines length
Preferred is 100 characters, but 120 is max.
Although modern monitors have relatively big resolution,
it's good for fast reading as well as opening two files side by side


### NamesPolicy
Use camelCase.

#### Constants
```c++
const int CamelCase = 121;
```

#### Private variables
Always ending with _.
```c++
QPoint position_;
```

#### Getters & setters
```c++
const QPoint & position() const;
void setPosition(const QPoint & position);
```

### Indentation
Use tabs, but code should look good no matter how wide is tabulation.

#### Wrapping long lines
TODO

#### Constructors
TODO


### Spacing

#### Pointers and references
```c++
const QString & name_;
QWidget * window_;
const QString & name() const;
QWidget * window();
ItemModel * const itemModel_;
```

#### Templates
```
QVector<QList<QPair <int, int>>> overlyComplexType;
static_cast<int>(number);
```


### Brackets
TODO

### Empty lines & File layout
TODO

### More
If something is not documented and you can't make your mind about coding style try to find answer
in [Linux kernel coding style](https://www.kernel.org/doc/Documentation/CodingStyle).


### Good programming rules
0. Keep const corectness.
1. Keep logic and graphics apart.
2. Don't hesitate to create new files, classes & functions.
3. Use forward declarations if possible.
4. [Single responsibility principle](http://en.wikipedia.org/wiki/Single_responsibility_principle)
5. [KISS principle](http://en.wikipedia.org/wiki/KISS_principle)
6. [DRY principle](http://en.wikipedia.org/wiki/Don%27t_repeat_yourself)
7. [Least astonishment principle](http://en.wikipedia.org/wiki/Principle_of_least_astonishment)
8. [Separation of concerns](http://en.wikipedia.org/wiki/Separation_of_concerns)
9. [Single source of truth](http://en.wikipedia.org/wiki/Single_Source_of_Truth)
10. [Do what I mean](http://en.wikipedia.org/wiki/DWIM)
11. [Information hiding](http://en.wikipedia.org/wiki/Information_hiding)
12. [Loose coupling](http://en.wikipedia.org/wiki/Loose_coupling)
13. [You aren't gonna need it](http://en.wikipedia.org/wiki/You_aren%27t_gonna_need_it)


 [project wiki]: https://github.com/Soszu/TheChroniclesOfAndaria/wiki
 [fork]: https://help.github.com/articles/fork-a-repo
 [pull request]: https://help.github.com/articles/using-pull-requests
