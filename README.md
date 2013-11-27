Zjednoczenie Andarii
==================

## About project

Zjednoczenie Andarii is an implementation of an innovative RPG board game.
> To learn more about go to [project wiki].

### Contributing

You can contribute to this project in one of three ways:

1. Browse issues, comment on proposals, report bugs.
2. Clone the project repo, make some changes according to
   development guidelines and issue a pull-request with your changes.
3. Share your opinions and ideas about game.
   For example you can sand me an email at <rsoszynski121@gmail.com>.

Not sure where to start? Look for issues listed on [project wiki].
These tasks not always require profound insight in source code,
so I guess that you will find something for yourself.

### Development guidelines

Simply use _Fork & Pull Model_

1. [Fork] this repo.
2. Write your code and insert it to your repo.
3. Create new [pull request].

### Coding style

Code style is based mostly on [Linux kernel coding style][Coding style] with the following
additions and modifications:

1. We don't enforce the limit on the length of lines.
2. Pointers and references bind to the right side (name of the variable) and
not the left side (type). This also applies to returning results from
functions, where we put space around the asterisk and ampersand characters.
Examples:
  * `int *a, *b;`
  * `const QString & f(const Object &o);`
3. We follow camelCase naming convention. Type names (including classes) and
constants start with a CapitalLetter.
4. Angle-parens in template types are prefixed and suffixed with a space:
 * WRONG: `QVector<QList<QPair<int, int> > >`
 * CORRECT: `QVector <QList <QPair <int, int> > >`
5. Angle-parens in template functions and entities with function-like syntax
(e.g. casts) are not prefixed nor suffixed with a space:
 * `static_cast<int>(x);`

 [project wiki]: https://github.com/Soszu/ZjednoczenieAndarii/wiki
 [fork]: https://help.github.com/articles/fork-a-repo
 [pull request]: https://help.github.com/articles/using-pull-requests
 [coding style]: https://www.kernel.org/doc/Documentation/CodingStyle
