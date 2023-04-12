// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "grammar.tab.hh"


// Unqualified %code blocks.
#line 20 "grammar.y"

    #include "../driver/driver.hpp"
    yy::parser::token_type yylex(yy::parser::semantic_type* yylval, yy::parser::location_type* l, Driver* driver);

#line 50 "grammar.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 141 "grammar.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Driver* driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 42: // NUMBER
        value.move< double > (std::move (that.value));
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.move< std::shared_ptr<BaseNode> > (std::move (that.value));
        break;

      case 41: // ID
      case 50: // param
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 42: // NUMBER
        value.copy< double > (YY_MOVE (that.value));
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.copy< std::shared_ptr<BaseNode> > (YY_MOVE (that.value));
        break;

      case 41: // ID
      case 50: // param
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 42: // NUMBER
        value.move< double > (YY_MOVE (s.value));
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.move< std::shared_ptr<BaseNode> > (YY_MOVE (s.value));
        break;

      case 41: // ID
      case 50: // param
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 42: // NUMBER
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.YY_MOVE_OR_COPY< std::shared_ptr<BaseNode> > (YY_MOVE (that.value));
        break;

      case 41: // ID
      case 50: // param
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 42: // NUMBER
        value.move< double > (YY_MOVE (that.value));
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.move< std::shared_ptr<BaseNode> > (YY_MOVE (that.value));
        break;

      case 41: // ID
      case 50: // param
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 42: // NUMBER
        value.copy< double > (that.value);
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.copy< std::shared_ptr<BaseNode> > (that.value);
        break;

      case 41: // ID
      case 50: // param
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 42: // NUMBER
        value.move< double > (that.value);
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        value.move< std::shared_ptr<BaseNode> > (that.value);
        break;

      case 41: // ID
      case 50: // param
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 42: // NUMBER
        yylhs.value.emplace< double > ();
        break;

      case 44: // program
      case 45: // global_scope
      case 46: // global_decl
      case 47: // decl_func
      case 48: // func_sign
      case 49: // params
      case 51: // args
      case 52: // arg
      case 53: // func_scope
      case 54: // open_func
      case 55: // func_stmts
      case 56: // close_func
      case 57: // return
      case 58: // stmts
      case 59: // stmt
      case 60: // scope
      case 61: // open_scope
      case 62: // close_scope
      case 63: // decl
      case 64: // decl_var
      case 65: // call
      case 66: // assign
      case 67: // name
      case 68: // expr
      case 69: // if_stmt
      case 70: // while_stmt
      case 71: // cond
      case 72: // input
      case 73: // output
        yylhs.value.emplace< std::shared_ptr<BaseNode> > ();
        break;

      case 41: // ID
      case 50: // param
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 126 "grammar.y"
                                                    { driver->start(); }
#line 988 "grammar.tab.cc"
    break;

  case 3:
#line 129 "grammar.y"
                                                    { driver->addStmt(yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 994 "grammar.tab.cc"
    break;

  case 4:
#line 130 "grammar.y"
                                                    { driver->addStmt(yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1000 "grammar.tab.cc"
    break;

  case 5:
#line 133 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1006 "grammar.tab.cc"
    break;

  case 6:
#line 134 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1012 "grammar.tab.cc"
    break;

  case 7:
#line 137 "grammar.y"
                                                    {
                                                        // both definition and declaration
                                                        auto decl_node = std::static_pointer_cast<DeclFuncNode>(yystack_[1].value.as < std::shared_ptr<BaseNode> > ());
                                                        std::weak_ptr<DeclFuncNode> decl = decl_node;

                                                        auto scope = std::static_pointer_cast<ScopeNode>(yystack_[0].value.as < std::shared_ptr<BaseNode> > ());
                                                        auto func_node = std::make_shared<FuncNode>(decl, scope);

                                                        decl_node->setFuncNode(func_node);
                                                        decl_node->defineFunc();
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = decl_node;
                                                    }
#line 1029 "grammar.tab.cc"
    break;

  case 8:
#line 149 "grammar.y"
                                                    {
                                                        // just declaration without definition
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[1].value.as < std::shared_ptr<BaseNode> > ();
                                                        driver->clearParams();
                                                        driver->setCurFunction("global");
                                                    }
#line 1040 "grammar.tab.cc"
    break;

  case 9:
#line 157 "grammar.y"
                                                     {
                                                        driver->setCurFunction(yystack_[3].value.as < std::string > ());
                                                        auto node = driver->find(yystack_[3].value.as < std::string > ());
                                                        if(node != nullptr && node->getExprType() == exprType::FUNC)
                                                        {
                                                            auto func_node = std::static_pointer_cast<DeclFuncNode>(node);
                                                            if(func_node->isDefined()) // ODR violation
                                                                throw std::runtime_error("Error: redeclaration of function\n");
                                                            else
                                                                yylhs.value.as < std::shared_ptr<BaseNode> > () = node;
                                                        }
                                                        else
                                                        {
                                                            auto new_node = std::make_shared<DeclFuncNode>(yystack_[3].value.as < std::string > (), driver->getFuncParams());
                                                            driver->insertName(yystack_[3].value.as < std::string > (), new_node);
                                                            yylhs.value.as < std::shared_ptr<BaseNode> > () = new_node;
                                                        }
                                                    }
#line 1063 "grammar.tab.cc"
    break;

  case 10:
#line 175 "grammar.y"
                                                    {
                                                        auto node = driver->find(yystack_[2].value.as < std::string > ());
                                                        if(node != nullptr && node->getExprType() == exprType::FUNC)
                                                        {
                                                            auto func_node = std::static_pointer_cast<DeclFuncNode>(node);
                                                            if(func_node->isDefined()) // ODR violation
                                                                throw std::runtime_error("Error: redeclaration of function\n");
                                                            else
                                                                yylhs.value.as < std::shared_ptr<BaseNode> > () = node;
                                                        }
                                                        else
                                                        {
                                                            auto new_node = std::make_shared<DeclFuncNode>(yystack_[2].value.as < std::string > ());
                                                            driver->insertName(yystack_[2].value.as < std::string > (), new_node);
                                                            yylhs.value.as < std::shared_ptr<BaseNode> > () = new_node;
                                                        }
                                                    }
#line 1085 "grammar.tab.cc"
    break;

  case 11:
#line 194 "grammar.y"
                                                    { driver->insertFuncParam(yystack_[0].value.as < std::string > ()); }
#line 1091 "grammar.tab.cc"
    break;

  case 12:
#line 195 "grammar.y"
                                                    { driver->insertFuncParam(yystack_[2].value.as < std::string > ()); }
#line 1097 "grammar.tab.cc"
    break;

  case 13:
#line 198 "grammar.y"
                                                    { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1103 "grammar.tab.cc"
    break;

  case 14:
#line 201 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1109 "grammar.tab.cc"
    break;

  case 15:
#line 204 "grammar.y"
                                                    { 
                                                        auto scope = std::make_shared<ScopeNode>(driver->getGlobalScope());
                                                        driver->setScope(scope);

                                                        auto&& params = driver->getFuncParams();
                                                        for(auto&& param : params)
                                                        {
                                                            auto var_node = std::make_shared<VarNode>(param);
                                                            auto decl_node = std::make_shared<DeclVarNode>(param, var_node);
                                                            scope->insert(param, decl_node);
                                                        }
                                                        driver->clearParams();
                                                    }
#line 1127 "grammar.tab.cc"
    break;

  case 16:
#line 219 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1133 "grammar.tab.cc"
    break;

  case 17:
#line 220 "grammar.y"
                                                    {}
#line 1139 "grammar.tab.cc"
    break;

  case 18:
#line 222 "grammar.y"
                                                    { 
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = driver->getScope();
                                                        driver->setScope(driver->getGlobalScope());
                                                        driver->setCurFunction("global");
                                                    }
#line 1149 "grammar.tab.cc"
    break;

  case 19:
#line 229 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<RetNode>(yystack_[1].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1155 "grammar.tab.cc"
    break;

  case 20:
#line 232 "grammar.y"
                                                    { driver->addStmt(yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1161 "grammar.tab.cc"
    break;

  case 21:
#line 233 "grammar.y"
                                                    { driver->addStmt(yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1167 "grammar.tab.cc"
    break;

  case 22:
#line 237 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1173 "grammar.tab.cc"
    break;

  case 23:
#line 238 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1179 "grammar.tab.cc"
    break;

  case 24:
#line 239 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[1].value.as < std::shared_ptr<BaseNode> > (); }
#line 1185 "grammar.tab.cc"
    break;

  case 25:
#line 240 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1191 "grammar.tab.cc"
    break;

  case 26:
#line 241 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1197 "grammar.tab.cc"
    break;

  case 27:
#line 242 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1203 "grammar.tab.cc"
    break;

  case 28:
#line 243 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1209 "grammar.tab.cc"
    break;

  case 29:
#line 244 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1215 "grammar.tab.cc"
    break;

  case 30:
#line 245 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1221 "grammar.tab.cc"
    break;

  case 31:
#line 250 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1227 "grammar.tab.cc"
    break;

  case 32:
#line 253 "grammar.y"
                                                    { driver->setScope(std::make_shared<ScopeNode>(driver->getScope())); }
#line 1233 "grammar.tab.cc"
    break;

  case 33:
#line 256 "grammar.y"
                                                    {
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = driver->getScope();
                                                        driver->setPrevScope();
                                                    }
#line 1242 "grammar.tab.cc"
    break;

  case 34:
#line 262 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1248 "grammar.tab.cc"
    break;

  case 35:
#line 265 "grammar.y"
                                                    {
                                                        auto node = driver->findInCurrentScope(yystack_[1].value.as < std::string > ());
                                                        if(node != nullptr) // ODR violation
                                                        {
                                                            // TODO: correct text if func name = var name
                                                            throw std::runtime_error("Error: redeclaration of variable\n");
                                                        }

                                                        auto var_node = std::make_shared<VarNode>(yystack_[1].value.as < std::string > ());
                                                        auto decl_node = std::make_shared<DeclVarNode>(yystack_[1].value.as < std::string > (), var_node);
                                                        driver->insertName(yystack_[1].value.as < std::string > (), decl_node);
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = decl_node;
                                                    }
#line 1266 "grammar.tab.cc"
    break;

  case 36:
#line 278 "grammar.y"
                                                    {
                                                        auto node = driver->findInCurrentScope(yystack_[3].value.as < std::string > ());
                                                        if(node != nullptr) // ODR violation
                                                        {
                                                            // TODO: correct text if func name = var name
                                                            throw std::runtime_error("Error: redeclaration of variable\n");
                                                        }

                                                        auto var_node = std::make_shared<VarNode>(yystack_[3].value.as < std::string > ());
                                                        auto decl_node = std::make_shared<DeclVarNode>(yystack_[3].value.as < std::string > (), var_node);
                                                        driver->insertName(yystack_[3].value.as < std::string > (), decl_node);

                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(var_node, binOpType::ASSIGN, yystack_[1].value.as < std::shared_ptr<BaseNode> > ());
                                                    }
#line 1285 "grammar.tab.cc"
    break;

  case 37:
#line 294 "grammar.y"
                                                    {
                                                        auto node = driver->findInGlobalScope(yystack_[3].value.as < std::string > ());
                                                        if(node == nullptr || node->getExprType() != exprType::FUNC)
                                                            throw std::runtime_error("Error: calling unknown function\n");

                                                        auto func_decl = std::static_pointer_cast<DeclFuncNode>(node);
                                                        auto&& func_args = driver->getFuncArgs();

                                                        bool isRecursive = false;
                                                        if(yystack_[3].value.as < std::string > () == driver->getCurFunction())
                                                            isRecursive = true;

                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<CallNode>(yystack_[3].value.as < std::string > (), isRecursive, func_decl->getFuncNode(), 
                                                                                        driver->getScope(), func_args);
                                                        driver->clearArgs();
                                                    }
#line 1306 "grammar.tab.cc"
    break;

  case 38:
#line 310 "grammar.y"
                                                    {
                                                        auto node = driver->findInGlobalScope(yystack_[2].value.as < std::string > ());
                                                        if(node == nullptr || node->getExprType() != exprType::FUNC)
                                                            throw std::runtime_error("Error: calling unknown function\n");

                                                        bool isRecursive = false;
                                                        if(yystack_[2].value.as < std::string > () == driver->getCurFunction())
                                                            isRecursive = true;

                                                        auto func_decl = std::static_pointer_cast<DeclFuncNode>(node);
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<CallNode>(yystack_[2].value.as < std::string > (), isRecursive, func_decl->getFuncNode(), 
                                                                                        driver->getScope());
                                                    }
#line 1324 "grammar.tab.cc"
    break;

  case 39:
#line 325 "grammar.y"
                                                    { driver->insertFuncArg(yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1330 "grammar.tab.cc"
    break;

  case 40:
#line 326 "grammar.y"
                                                    { driver->insertFuncArg(yystack_[2].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1336 "grammar.tab.cc"
    break;

  case 41:
#line 329 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1342 "grammar.tab.cc"
    break;

  case 42:
#line 332 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[3].value.as < std::shared_ptr<BaseNode> > (), binOpType::ASSIGN, yystack_[1].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1348 "grammar.tab.cc"
    break;

  case 43:
#line 335 "grammar.y"
                                                    {
                                                        auto node = driver->find(yystack_[0].value.as < std::string > ());
                                                        if(node == nullptr)
                                                            throw std::runtime_error("Error: variable was not declared\n");
                                                        else if(node->getExprType() != exprType::VAR)
                                                            throw std::runtime_error("Error: name is not a variable\n");
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = std::static_pointer_cast<DeclVarNode>(node)->getVarNode();
                                                    }
#line 1361 "grammar.tab.cc"
    break;

  case 44:
#line 345 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::ADD, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1367 "grammar.tab.cc"
    break;

  case 45:
#line 346 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::SUB, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1373 "grammar.tab.cc"
    break;

  case 46:
#line 347 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::MUL, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1379 "grammar.tab.cc"
    break;

  case 47:
#line 348 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::DIV, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1385 "grammar.tab.cc"
    break;

  case 48:
#line 349 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::MOD, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1391 "grammar.tab.cc"
    break;

  case 49:
#line 350 "grammar.y"
                                                    {   
                                                        auto decl_node = driver->find(yystack_[0].value.as < std::string > ());
                                                        if(decl_node == nullptr)
                                                        {
                                                            std::cout << yystack_[0].value.as < std::string > () << std::endl;
                                                            throw std::runtime_error("Error: unknown variable\n");
                                                        }
                                                        auto var_node = std::static_pointer_cast<DeclVarNode>(decl_node);
                                                        yylhs.value.as < std::shared_ptr<BaseNode> > () = var_node->getVarNode();
                                                    }
#line 1406 "grammar.tab.cc"
    break;

  case 50:
#line 360 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<ConstNode>(yystack_[0].value.as < double > ()); }
#line 1412 "grammar.tab.cc"
    break;

  case 51:
#line 361 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[1].value.as < std::shared_ptr<BaseNode> > (); }
#line 1418 "grammar.tab.cc"
    break;

  case 52:
#line 362 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1424 "grammar.tab.cc"
    break;

  case 53:
#line 365 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<IfNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1430 "grammar.tab.cc"
    break;

  case 54:
#line 366 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<IfNode>(yystack_[4].value.as < std::shared_ptr<BaseNode> > (), yystack_[2].value.as < std::shared_ptr<BaseNode> > (), yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1436 "grammar.tab.cc"
    break;

  case 55:
#line 369 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<WhileNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1442 "grammar.tab.cc"
    break;

  case 56:
#line 372 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::AND, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1448 "grammar.tab.cc"
    break;

  case 57:
#line 373 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::OR, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1454 "grammar.tab.cc"
    break;

  case 58:
#line 374 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<UnOpNode>(yystack_[0].value.as < std::shared_ptr<BaseNode> > (), unOpType::NOT); }
#line 1460 "grammar.tab.cc"
    break;

  case 59:
#line 375 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[1].value.as < std::shared_ptr<BaseNode> > (); }
#line 1466 "grammar.tab.cc"
    break;

  case 60:
#line 376 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = yystack_[0].value.as < std::shared_ptr<BaseNode> > (); }
#line 1472 "grammar.tab.cc"
    break;

  case 61:
#line 377 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::EQUAL, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1478 "grammar.tab.cc"
    break;

  case 62:
#line 378 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::NOT_EQUAL, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1484 "grammar.tab.cc"
    break;

  case 63:
#line 379 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::LESS, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1490 "grammar.tab.cc"
    break;

  case 64:
#line 380 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::GREATER, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1496 "grammar.tab.cc"
    break;

  case 65:
#line 381 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::LESS_EQ, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1502 "grammar.tab.cc"
    break;

  case 66:
#line 382 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<BinOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), binOpType::GREATER_EQ, yystack_[0].value.as < std::shared_ptr<BaseNode> > ()); }
#line 1508 "grammar.tab.cc"
    break;

  case 67:
#line 385 "grammar.y"
                                                    { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<UnOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), unOpType::SCAN); }
#line 1514 "grammar.tab.cc"
    break;

  case 68:
#line 388 "grammar.y"
                                                   { yylhs.value.as < std::shared_ptr<BaseNode> > () = std::make_shared<UnOpNode>(yystack_[2].value.as < std::shared_ptr<BaseNode> > (), unOpType::PRINT); }
#line 1520 "grammar.tab.cc"
    break;


#line 1524 "grammar.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -103;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -24,   -34,   -20,    32,   -24,  -103,  -103,     7,  -103,    20,
       8,  -103,  -103,  -103,  -103,  -103,    86,   -11,  -103,    -6,
    -103,    24,    25,    31,    49,    -6,    56,    65,  -103,    86,
    -103,  -103,    86,  -103,  -103,    71,  -103,    67,  -103,  -103,
    -103,  -103,  -103,  -103,    68,    96,    -6,    56,  -103,  -103,
     139,   -13,   -13,    -6,    73,   146,    -3,  -103,  -103,  -103,
      74,  -103,    -6,  -103,    76,    80,  -103,    -6,    -6,    -6,
      -6,    -6,   -13,   -13,   123,    21,    53,    88,  -103,    98,
    -103,  -103,    99,   105,   158,  -103,  -103,   153,  -103,  -103,
      55,    55,  -103,  -103,  -103,  -103,    52,    82,    -6,    -6,
      -6,    -6,    -6,    -6,   -13,   -13,   102,   102,   120,   130,
    -103,    -6,  -103,  -103,   158,   158,   158,   158,   158,   158,
    -103,   115,   104,  -103,  -103,  -103,  -103,   102,  -103
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     2,     3,     5,     0,     6,     0,
       0,     1,     4,     8,    15,     7,    17,     0,    35,     0,
      32,     0,     0,     0,     0,     0,    43,     0,    30,    16,
      20,    22,     0,    23,    34,     0,    25,     0,    26,    27,
      28,    29,    10,    13,     0,    11,     0,    49,    50,    52,
       0,     0,     0,     0,     0,     0,     0,    18,    14,    21,
       0,    24,     0,     9,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,    60,     0,     0,     0,    43,     0,
      19,    38,     0,    39,    41,    33,    31,     0,    12,    51,
      44,    45,    46,    47,    48,    58,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    42,    59,    62,    61,    63,    64,    65,    66,
      56,    57,    53,    55,    68,    67,    40,     0,    54
  };

  const short
  parser::yypgoto_[] =
  {
    -103,  -103,  -103,   164,  -103,  -103,    79,  -103,    39,  -103,
    -103,  -103,  -103,  -103,  -103,   125,   -27,  -102,  -103,  -103,
    -103,    22,   -15,  -103,   116,   -19,  -103,  -103,   -49,  -103,
    -103
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,     7,    44,    45,    82,    83,
      15,    16,    27,    58,    28,    29,    30,    31,    32,    86,
      33,    34,    49,    36,    37,    74,    38,    39,    75,    40,
      41
  };

  const unsigned char
  parser::yytable_[] =
  {
      50,    35,    59,    76,   122,   123,    55,     9,    72,    73,
      13,    18,    42,     1,    35,     2,    46,    35,    19,    46,
      81,    10,     8,    95,    97,   128,     8,    65,    47,    48,
      43,    14,    11,    59,    77,    47,    48,    84,    47,    48,
     104,   105,    17,    87,   106,    35,    51,    52,    90,    91,
      92,    93,    94,    53,    96,   120,   121,    67,    68,    69,
      70,    71,    69,    70,    71,    98,    99,   100,   101,   102,
     103,    54,   104,   105,    61,    89,   107,    62,    56,   114,
     115,   116,   117,   118,   119,    67,    68,    69,    70,    71,
      57,    63,    84,    67,    68,    69,    70,    71,    20,    85,
      64,   104,   105,    89,    21,   113,    22,    23,    24,   111,
      20,   108,    25,     2,    78,    26,    21,    43,    22,    23,
      24,   109,   110,   124,    25,     2,    20,    26,    67,    68,
      69,    70,    71,   125,   104,   127,    98,    99,   100,   101,
     102,   103,    66,    88,    67,    68,    69,    70,    71,    80,
     126,    67,    68,    69,    70,    71,   112,    60,    67,    68,
      69,    70,    71,    67,    68,    69,    70,    71,    12,     0,
      79
  };

  const signed char
  parser::yycheck_[] =
  {
      19,    16,    29,    52,   106,   107,    25,    41,    21,    22,
       3,     3,    23,    37,    29,    39,    22,    32,    10,    22,
      23,    41,     0,    72,    73,   127,     4,    46,    41,    42,
      41,    24,     0,    60,    53,    41,    42,    56,    41,    42,
      19,    20,    22,    62,    23,    60,    22,    22,    67,    68,
      69,    70,    71,    22,    73,   104,   105,     5,     6,     7,
       8,     9,     7,     8,     9,    13,    14,    15,    16,    17,
      18,    22,    19,    20,     3,    23,    23,    10,    22,    98,
      99,   100,   101,   102,   103,     5,     6,     7,     8,     9,
      25,    23,   111,     5,     6,     7,     8,     9,    24,    25,
       4,    19,    20,    23,    30,    23,    32,    33,    34,     4,
      24,    23,    38,    39,    41,    41,    30,    41,    32,    33,
      34,    23,    23,     3,    38,    39,    24,    41,     5,     6,
       7,     8,     9,     3,    19,    31,    13,    14,    15,    16,
      17,    18,     3,    64,     5,     6,     7,     8,     9,     3,
     111,     5,     6,     7,     8,     9,     3,    32,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     4,    -1,
      54
  };

  const signed char
  parser::yystos_[] =
  {
       0,    37,    39,    44,    45,    46,    47,    48,    64,    41,
      41,     0,    46,     3,    24,    53,    54,    22,     3,    10,
      24,    30,    32,    33,    34,    38,    41,    55,    57,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    69,    70,
      72,    73,    23,    41,    49,    50,    22,    41,    42,    65,
      68,    22,    22,    22,    22,    68,    22,    25,    56,    59,
      58,     3,    10,    23,     4,    68,     3,     5,     6,     7,
       8,     9,    21,    22,    68,    71,    71,    68,    41,    67,
       3,    23,    51,    52,    68,    25,    62,    68,    49,    23,
      68,    68,    68,    68,    68,    71,    68,    71,    13,    14,
      15,    16,    17,    18,    19,    20,    23,    23,    23,    23,
      23,     4,     3,    23,    68,    68,    68,    68,    68,    68,
      71,    71,    60,    60,     3,     3,    51,    31,    60
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    43,    44,    45,    45,    46,    46,    47,    47,    48,
      48,    49,    49,    50,    53,    54,    55,    55,    56,    57,
      58,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60,    61,    62,    63,    64,    64,    65,    65,    51,
      51,    52,    66,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    72,    73
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     2,     2,     5,
       4,     1,     3,     1,     3,     1,     1,     0,     1,     3,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     5,     4,     3,     1,
       3,     1,     4,     1,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     5,     7,     5,     3,     3,     2,     3,
       1,     3,     3,     3,     3,     3,     3,     5,     5
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "\";\"", "\",\"", "\"+\"", "\"-\"",
  "\"*\"", "\"/\"", "\"%\"", "\"=\"", "\"++\"", "\"--\"", "\"!=\"",
  "\"==\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"&&\"", "\"||\"",
  "\"!\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\"?\"",
  "\":\"", "\"if\"", "\"else\"", "\"while\"", "\"print\"", "\"scan\"",
  "\"break\"", "\"continue\"", "\"func\"", "\"return\"", "\"var\"",
  "\"array\"", "ID", "NUMBER", "$accept", "program", "global_scope",
  "global_decl", "decl_func", "func_sign", "params", "param", "args",
  "arg", "func_scope", "open_func", "func_stmts", "close_func", "return",
  "stmts", "stmt", "scope", "open_scope", "close_scope", "decl",
  "decl_var", "call", "assign", "name", "expr", "if_stmt", "while_stmt",
  "cond", "input", "output", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   126,   126,   129,   130,   133,   134,   137,   149,   157,
     175,   194,   195,   198,   201,   204,   219,   220,   222,   229,
     232,   233,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   250,   253,   256,   262,   265,   278,   294,   310,   325,
     326,   329,   332,   335,   345,   346,   347,   348,   349,   350,
     360,   361,   362,   365,   366,   369,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   385,   388
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
    };
    const int user_token_number_max_ = 297;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 2055 "grammar.tab.cc"

#line 392 "grammar.y"


// Main parsing function: just delegate driver's parser
yy::parser::token_type yylex (yy::parser::semantic_type* yylval, yy::parser::location_type* l, Driver* driver)
{
    return driver->yylex(l, yylval);
}

void yy::parser::error(const yy::parser::location_type& loc, const std::string& message)
{
    std::cerr << message << " in line " << loc.begin.line << std::endl;
}
