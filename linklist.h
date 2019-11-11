#include <iostream>
using namespace std;
#include "string"
//#include"Token.h"

class linklist
{
public:
  string cp;
  string vp;
  int lineno;
  linklist *next;

  void insert(string cp, string vp, int lineno, linklist **start)
  {
    linklist *ptr = new linklist;

    ptr->cp = cp;
    ptr->vp = vp;
    ptr->lineno = lineno;
    ptr->next = NULL;
    if (*start == NULL)
    {
      *start = ptr;
    }
    else
    {
      linklist *curr = *start;
      while (curr->next != NULL)
      {
        curr = curr->next;
      }
      curr->next = ptr;
    }
  }

  bool start(linklist **start)
  {
    //linklist list1;
    linklist *curr = *start;
    if (curr->cp == "class" || curr->cp == "DT" || curr->cp == "ID" || curr->cp == "static" || curr->cp == "void" || curr->cp == "int")
    {
      if (defs(&curr))
      {
        if (VI(&curr))
        {
          if (curr->cp == "main")
          {
            curr = curr->next;
            if (curr->cp == "(")
            {
              curr = curr->next;
              if (NV(&curr))
              {
                if (curr->cp == "{")
                {
                  curr = curr->next;
                  if (MST(&curr))
                  {
                    if (curr->cp == "}")
                    {
                      curr = curr->next;
                      if (curr->cp == "$")
                      {
                        cout << "File end" << endl;
                        return true;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      cout << "Error syntax at:  " << curr->cp << endl;
      return false;
    }
  }

  bool VI(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "void" || curr->cp == "DT")
    {
      cout << "Curr value at top " << curr->cp << endl;
      curr = curr->next;
      return true;
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool NV(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "void" || curr->cp == ")")
    {
      if (curr->cp == "void")
      {
        curr = curr->next;
        return true;
      }
      else if (curr->cp == ")")
      {
        curr = curr->next;
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool defs(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "class" || curr->cp == "ID" || curr->cp == "DT" || curr->cp == "static" || curr->cp == "void" || curr->cp == "int")
    {
      if (classs(&curr))
      {
        if (defs(&curr))
        {
          return true;
        }
      }
      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (defs1(&curr))
        {
          if (defs(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (defs2(&curr))
          {
            if (defs(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "static")
      {
        curr = curr->next;
        if (type(&curr))
        {
          if (curr->cp == ")")
          {
            curr = curr->next;
            if (fun_dec(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "void" || curr->cp == "int") //jam
      {
        cout << "Returnung void" << endl;
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool classs(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "class")
    {
      curr = curr->next;
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (check_inh(&curr))
        {
          if (curr->cp == "{")
          {
            curr = curr->next;
            if (class_body(&curr))
            {
              if (curr->cp == "}")
              {
                curr = curr->next;
                if (curr->cp == ";")
                {
                  curr = curr->next;
                  return true;
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      // cout<<"Error syntax at class: "<<curr->cp<<endl;
      return false;
    }
  }
  bool class_body(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "DT" || curr->cp == "AM" || curr->cp == "virtual" || curr->cp == "const" || curr->cp == "static" || curr->cp == "}")
    {
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (X1(&curr))
        {
          if (class_body(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (X2(&curr))
          {
            if (class_body(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else if (curr->cp == "AM")
      {
        curr = curr->next;
        if (curr->cp == ";")
        {
          curr = curr->next;
          if (class_body(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (word(&curr))
      {
        if (type(&curr))
        {
          if (curr->cp == "(")
          {
            curr = curr->next;
            if (fun_dec(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else if (curr->cp == "}")
      {
        return true;
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool word(linklist **start)
  {
    linklist *curr = *start;

    if (curr->cp == "virtual" || curr->cp == "const" || curr->cp == "static")
    {
      curr = curr->next;
      return true;
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool X1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "(" || curr->cp == "ID")
    {
      if (constructor_fn(&curr))
      {
        return true;
      }
      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (X3(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool constructor_fn(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "(")
    {
      if (para(&curr))
      {
        if (curr->cp == ")")
        {
          curr = curr->next;
          if (curr->cp == "{")
          {
            curr = curr->next;
            if (MST(&curr))
            {
              if (curr->cp == "}")
              {
                curr = curr->next;
                return true;
              }
            }
          }
        }
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool X2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "(" || curr->cp == "AOP" || curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (fun_dec(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (dt_dec(&curr))
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool X3(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "(" || curr->cp == "ID" || curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (fun_dec(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (obj_dec(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool defs1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == "ID")
    {
      if (ass_st(&curr))
      {
        return true;
      }
      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (X(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool X(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "=" || curr->cp == ";" || curr->cp == "(" || curr->cp == ",")
    {
      if (obj_dec(&curr))
      {
        return true;
      }
      else if (curr->cp == "(")
      {
        curr = curr->next;
        if (terminal(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool terminal(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "=" || curr->cp == ";" || curr->cp == "(" || curr->cp == ",")
    {
      if (fun_dec(&curr))
      {
        return true;
      }
      else if (constructor_dec(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool defs2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "=" || curr->cp == ";" || curr->cp == "(" || curr->cp == ",")
    {

      if (dt_dec(&curr))
      {
        return true;
      }
      else if (curr->cp == "(")
      {
        curr = curr->next;
        if (fun_dec(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool type(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "DT")
    {
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool fun_dec(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "DT" || curr->cp == "void" || curr->cp == ")")
    {
      if (para(&curr))
      {
        if (curr->cp == ")")
        {
          curr = curr->next;
          if (inherit(&curr))
          {
            if (curr->cp == "{")
            {
              curr = curr->next;
              if (MST(&curr))
              {
                if (curr->cp == "}")
                {
                  curr = curr->next;
                  return true;
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool inherit(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == ":")
    {
      curr = curr->next;
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (fn_call1(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool def(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "DT")
    {
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool check_inh(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == ":" || curr->cp == "{")
    {
      if (curr->cp == ":")
      {
        curr = curr->next;
        if (curr->cp == "AM")
        {
          curr = curr->next;
          if (curr->cp == "ID")
          {
            curr = curr->next;
            return true;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool para(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "DT" || curr->cp == "void" || curr->cp == ")")
    {
      if (def(&curr))
      {
        if (E(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "void")
      {
        curr = curr->next;
        return true;
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool E(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == ",")
      {
        curr = curr->next;
        if (def(&curr))
        {
          if (E(&curr))
          {
            return true;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool MST(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "if" || curr->cp == "while" || curr->cp == "switch" || curr->cp == "for" || curr->cp == "return" || curr->cp == "continue" || curr->cp == "break" || curr->cp == "ID" || curr->cp == "DT" || curr->cp == "}")
    {
      if (SST(&curr))
      {
        if (MST(&curr))
        {
          return true;
        }
      }
      else if (curr->cp == "}")
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool SST(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "if" || curr->cp == "while" || curr->cp == "switch" || curr->cp == "for" || curr->cp == "return" || curr->cp == "continue" || curr->cp == "break" || curr->cp == "ID" || curr->cp == "DT")
    {
      if (if_else(&curr))
      {
        return true;
      }
      else if (while_st(&curr))
      {
        return true;
      }
      else if (switch_st(&curr))
      {
        return true;
      }
      else if (for_st(&curr))
      {
        return true;
      }
      else if (return_st(&curr))
      {
        return true;
      }

      else if (curr->cp == "continue")
      {
        curr = curr->next;
        if (curr->cp == ";")
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }

      else if (curr->cp == "break")
      {
        curr = curr->next;
        if (curr->cp == ";")
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }

      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (SST1(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }

      else if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (SST2(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool dt_dec(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "AOP" || curr->cp == "," || curr->cp == ";")
    {
      if (new_array(&curr))
      {
        return true;
      }
      else if (init(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool new_array(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[")
    {
      curr = curr->next;
      if (OE(&curr))
      {
        if (curr->cp == "]")
        {
          curr = curr->next;
          if (array2(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool array2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "=" || curr->cp == ";")
    {
      if (curr->cp == "=")
      {
        curr = curr->next;
        if (curr->cp == "{")
        {
          curr = curr->next;
          if (array3(&curr))
          {
            if (curr->cp == "}")
            {
              curr = curr->next;
              if (curr->cp == ";")
              {
                return true;
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == ";")
      {
        curr = curr->next;
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool array3(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "ID" || curr->cp == "(" || curr->cp == "!")
    {
      if (OE(&curr))
      {
        if (array4(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool array4(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "," || curr->cp == "}")
    {
      if (curr->cp == ",")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (array4(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool init(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == "AOP")
      {
        curr = curr->next;
        if (init2(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        if (list(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool init2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "ID" || curr->cp == "!")
    {
      if (OE(&curr))
      {
        if (curr->cp == ";")
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (init4(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool init3(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == "AOP")
      {
        curr = curr->next;
        if (init4(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool init4(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "const")
    {
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (init3(&curr))
        {
          if (list(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "const")
      {
        curr = curr->next;
        if (list(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool list(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == ",")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (init3(&curr))
          {
            if (list(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else if (curr->cp == ";")
      {
        curr = curr->next;
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool obj_dec(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "=" || curr->cp == "," || curr->cp == ";")
    {
      if (array(&curr))
      {
        if (new_init(&curr))
        {
          if (list2(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool new_init(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == "," || curr->cp == ";")
    {
      if (curr->cp == "=")
      {

        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (new_init(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          return true;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool list2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "," || curr->cp == ";")
    {

      if (curr->cp == ",")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (array(&curr))
          {
            if (new_init(&curr))
            {
              if (list2(&curr))
              {
                return true;
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == ";")
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool array(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "." || curr->cp == "(" || curr->cp == "inc_dec" || curr->cp == "AOP")
    {
      if (curr->cp == "[")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == "]")
          {
            curr = curr->next;
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool ass_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP")
    {
      if (ass_st1(&curr))
      {
        if (XX(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool ass_st1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP")
    {
      curr = curr->next;
      if (OE(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool XX(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == ";")
    {
      if (ass_st1(&curr))
      {
        if (XX(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == ";")
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool constructor_dec(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "ID" || curr->cp == "!" || curr->cp == ")")
    {
      if (arg(&curr))
      {
        if (curr->cp == ")")
        {
          curr = curr->next;
          if (curr->cp == ";")
          {
            curr = curr->next;
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool fn_call1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "." || curr->cp == ")")
    {
      if (check_id(&curr))
      {
        if (curr->cp == "(")
        {
          curr = curr->next;
          if (arg(&curr))
          {
            if (curr->cp == ")")
            {
              curr = curr->next;
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool check_id(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "." || curr->cp == "(")
    {
      if (curr->cp == ".")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (array(&curr))
          {
            if (check_id(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool arg(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "ID" || curr->cp == "!" || curr->cp == ")")
    {
      if (OE(&curr))
      {
        if (arg1(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool arg1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == ",")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (arg1(&curr))
          {
            return true;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool SST1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "." || curr->cp == "inc_dec" || curr->cp == "AOP" || curr->cp == "ID")
    {
      if (array(&curr))
      {
        if (L2(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (xxx(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool L2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "." || curr->cp == "(" || curr->cp == "inc_dec" || curr->cp == "AOP" || curr->cp == "ID")
    {
      if (fn_call(&curr))
      {
        return true;
      }
      else if (curr->cp == "inc_dec")
      {
        curr = curr->next;
        if (curr->cp == ";")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (ass_st(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool xxx(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "[" || curr->cp == "," || curr->cp == ";" || curr->cp == "ID" || curr->cp == "(")
    {
      if (obj_dec(&curr))
      {
        return true;
      }
      else if (curr->cp == "(")
      {
        curr = curr->next;
        if (constructor_dec(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool SST2(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == "[" || curr->cp == "," || curr->cp == ";")
    {
      if (dt_dec(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool fn_call(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "." || curr->cp == "(")
    {
      if (fn_call1(&curr))
      {
        if (curr->cp == ";")
        {
          curr = curr->next;
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool return_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "return")
    {
      curr = curr->next;
      if (OE1(&curr))
      {
        return true;
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool OE1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "!" || curr->cp == "ID" || curr->cp == "(" || curr->cp == ";")
    {
      if (OE(&curr))
      {
        return true;
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool if_else(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "if")
    {
      curr = curr->next;
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == ")")
          {
            curr = curr->next;
            if (curr->cp == "{")
            {
              curr = curr->next;
              if (MST(&curr))
              {
                if (curr->cp == "}")
                {
                  curr = curr->next;
                  if (optional_else(&curr))
                  {
                    return true;
                  }
                  else
                  {
                    cout << "Error syntax at: " << curr->cp << endl;
                    return false;
                  }
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool optional_else(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "else" || curr->cp == "if" || curr->cp == "switch" || curr->cp == "for" || curr->cp == "return" || curr->cp == "ID" || curr->cp == "DT" || curr->cp == "continue" || curr->cp == "break" || curr->cp == "}")
    {
      if (curr->cp == "else")
      {
        curr = curr->next;
        if (curr->cp == "{")
        {
          curr = curr->next;
          if (MST(&curr))
          {
            if (curr->cp == "}")
            {
              curr = curr->next;
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
  }
  bool while_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "while")
    {
      curr = curr->next;
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == ")")
          {
            curr = curr->next;
            if (curr->cp == "{")
            {
              curr = curr->next;
              if (MST(&curr))
              {
                if (curr->cp == "}")
                {
                  curr = curr->next;
                  return true;
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool switch_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "switch")
    {
      curr = curr->next;
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == ")")
          {
            curr = curr->next;
            if (curr->cp == "{")
            {
              curr = curr->next;
              if (case_st(&curr))
              {
                if (default_st(&curr))
                {
                  if (curr->cp == "}")
                  {
                    curr = curr->next;
                    return true;
                  }
                  else
                  {
                    cout << "Error syntax at: " << curr->cp << endl;
                    return false;
                  }
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool case_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "case" || curr->cp == "default" || curr->cp == "}")
    {
      if (curr->cp == "case")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == ":")
          {
            curr = curr->next;
            if (curr->cp == "{")
            {
              curr = curr->next;
              if (MST(&curr))
              {
                if (curr->cp == "}")
                {
                  curr = curr->next;
                  if (case_st(&curr))
                  {
                    return true;
                  }
                  else
                  {
                    cout << "Error syntax at: " << curr->cp << endl;
                    return false;
                  }
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool default_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "default" || curr->cp == "}")
    {
      if (curr->cp == "default")
      {
        curr = curr->next;
        if (curr->cp == ":")
        {
          curr = curr->next;
          if (curr->cp == "{")
          {
            curr = curr->next;
            if (MST(&curr))
            {
              if (curr->cp == "}")
              {
                curr = curr->next;
                return true;
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool for_st(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "for")
    {
      curr = curr->next;
      if (curr->cp == "(")
      {
        curr = curr->next;
        if (C1(&curr))
        {
          if (C2(&curr))
          {
            if (curr->cp == ";")
            {
              curr = curr->next;
              if (C3(&curr))
              {
                if (curr->cp == ")")
                {
                  curr = curr->next;
                  if (curr->cp == "{")
                  {
                    curr = curr->next;
                    if (MST(&curr))
                    {
                      if (curr->cp == "}")
                      {
                        curr = curr->next;
                        return true;
                      }
                      else
                      {
                        cout << "Error syntax at: " << curr->cp << endl;
                        return false;
                      }
                    }
                    else
                    {
                      cout << "Error syntax at: " << curr->cp << endl;
                      return false;
                    }
                  }
                  else
                  {
                    cout << "Error syntax at: " << curr->cp << endl;
                    return false;
                  }
                }
                else
                {
                  cout << "Error syntax at: " << curr->cp << endl;
                  return false;
                }
              }
              else
              {
                cout << "Error syntax at: " << curr->cp << endl;
                return false;
              }
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool C1(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "DT" || curr->cp == "ID" || curr->cp == ";")
    {
      if (curr->cp == "DT")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          if (dt_dec(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (ass_st(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == ";")
      {
        curr = curr->next;
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool C2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == ";" || curr->cp == "ID" || curr->cp == "!")
    {
      if (OE(&curr))
      {
        return true;
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool C3(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ID" || curr->cp == ")" || curr->cp == "inc_dec")
    {
      if (curr->cp == "ID")
      {
        curr = curr->next;
        if (X11(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "inc_dec")
      {
        curr = curr->next;
        return true;
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool X11(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "AOP" || curr->cp == "inc_dec")
    {
      if (ass_st(&curr))
      {
        return true;
      }
      else if (curr->cp == "inc_dec")
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool OE(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (AE(&curr))
      {
        if (OEE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool AE(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (RE(&curr))
      {
        if (AEE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool OEE(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "||" || curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == "||")
      {
        curr = curr->next;
        if (AEE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool RE(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (PE(&curr))
      {
        if (REE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool PE(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (ME(&curr))
      {
        if (PEE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool ME(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (F(&curr))
      {
        if (MEE(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool F(linklist **start)
  {

    linklist *curr = *start;
    if (curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (curr->cp == "const")
      {
        curr = curr->next;
        if (F(&curr))
        {
          return true;
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else if (curr->cp == "(")
      {
        curr = curr->next;
        if (OE(&curr))
        {
          if (curr->cp == ")")
          {
            curr = curr->next;
            if (F(&curr))
            {
              return true;
            }
          }
        }
      }

      else if (curr->cp == "!")
      {
        curr = curr->next;
        if (PE(&curr))
        {
          if (F(&curr))
          {
            return true;
          }
        }
      }

      else if (curr->cp == "ID")
      {
        curr = curr->next;
        if (XOE1(&curr))
        {
          if (F(&curr))
          {
            return true;
          }
        }
      }

      else
      {
        cout << "Error syntax at: " << curr->cp << endl;
        return false;
      }
    }
  }

  bool XOE1(linklist **start)
  {
    linklist *curr = *start;

    if (curr->cp == "[" || curr->cp == "const" || curr->cp == "(" || curr->cp == "!" || curr->cp == "ID")
    {
      if (fn_call(&curr))
      {
        return true;
      }
      else if (array(&curr))

      {
        if (nt2(&curr))
        {
          if (curr->cp == "inc_dec")
          {
            curr = curr->next;
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool nt2(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "." || curr->cp == "inc_dec")
    {
      if (curr->cp == ".")
      {
        curr = curr->next;
        if (curr->cp == "ID")
        {
          curr = curr->next;
          if (array(&curr))
          {
            if (nt2(&curr))
            {
              return true;
            }
            else
            {
              cout << "Error syntax at: " << curr->cp << endl;
              return false;
            }
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
        else
        {
          cout << "Error syntax at: " << curr->cp << endl;
          return false;
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  bool AEE(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "&&" || curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == "&&")
      {
        curr = curr->next;
        if (RE(&curr))
        {
          if (AEE(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool PEE(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "PM" || curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == "PM")
      {
        curr = curr->next;
        if (ME(&curr))
        {
          if (PEE(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool MEE(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "MDM" || curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == "MDM")
      {
        curr = curr->next;
        if (F(&curr))
        {
          if (MEE(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }
  bool REE(linklist **start)
  {
    linklist *curr = *start;
    if (curr->cp == "ROP" || curr->cp == "," || curr->cp == ")")
    {
      if (curr->cp == "ROP")
      {
        curr = curr->next;
        if (PE(&curr))
        {
          if (REE(&curr))
          {
            return true;
          }
          else
          {
            cout << "Error syntax at: " << curr->cp << endl;
            return false;
          }
        }
      }
      else
      {
        return true;
      }
    }
    else
    {
      cout << "Error syntax at: " << curr->cp << endl;
      return false;
    }
  }

  void print(linklist **start)
  {
    if (start == NULL)
    {
      cout << "List is empty" << endl;
    }
    else
    {
      linklist *curr = *start;
      while (curr->next != NULL)
      {
        cout << "CP :   " << curr->cp << "  ";
        cout << "VP :   " << curr->vp << "  ";
        cout << "Lineno :   " << curr->lineno << "  " << endl;
        curr = curr->next;
      }
      cout << "CP : " << curr->cp << "  ";
      cout << "VP : " << curr->vp << "  ";
      cout << "Lineno : " << curr->lineno << "  " << endl;
    }
  }

  //private:
  // string cp;
  // string vp;
  // int lineno;
  // linklist *next;
};