import scala.util.matching.Regex

// Unambiguous grammar
// E -> T + E | T
// T -> Const | Var

//S -: E$
//E -: T E2
// E2 -: '|' E3
// E2 -: NIL
//E3 -: T E2
// T -: F T2
// T2 -: F T2
// T2 -: NIL
//F -: A F2
// F2 -: '?' F2
// F2 -: NIL
//A -: C
//A -: '(' A2
// A2 -: E ')'
  object count{
  var countIndex=0
}
abstract class S {
  def eval(input:String): Boolean
}

abstract class A extends S
case class E(l: T, right: Option[E2]) extends S{
  def eval(input:String): Boolean = {
    val a1 = count.countIndex
    if (l.eval(input)) true
    else right match{
      case None => false
      case Some(right) => {
        count.countIndex = a1
        right.eval(input)
      }
    }
  }
}

case class E2(l: E3) extends S {
  def eval(input:String): Boolean = l.eval(input)
}
case class E3(l: T, right: Option[E2]) extends S{
  def eval(input:String): Boolean = {
    val a1 = count.countIndex
    if (l.eval(input)) true
    else right match{
      case None => false
      case Some(right) => {
        count.countIndex = a1
        right.eval(input)
      }
    }
  }
}

case class T(l: F, right: Option[T2]) extends S {
  def eval(input:String): Boolean = {
    if (!l.eval(input)) false
    else right match{
      case None => true
      case Some(right) => right.eval(input)
    }
  }
}



case class T2(l: F, right: Option[T2]) extends S {
  def eval(input:String): Boolean = {
    if (!l.eval(input)) false
    else right match{
      case None => true
      case Some(right) => right.eval(input)
    }
  }
}

case class F(l: A, right: Option[F2]) extends S {
  def eval(input:String): Boolean = {
    val a1 = count.countIndex
    if (l.eval(input)) true
    else {
      count.countIndex = a1
      right match{
        case None => false
        case Some(_) => true
      }
    }
  }
}
case class F2(l: Option[F2]) extends S{
  def eval(input:String): Boolean = false
}

case class A2(l:E) extends A{
  def eval(input:String):Boolean = l.eval(input)
}
case class C(v:Char) extends A{
  def eval(input:String): Boolean = {
    if (count.countIndex < input.length && v == '.') {
      count.countIndex += 1
      true
    } else
    if (count.countIndex < input.length && input(count.countIndex) == v){
      count.countIndex +=1
      true
    } else {
      false
    }
  }
}



class RecursiveDescent(input:String) {

  var index = 0

  def parseE(): E = E(parseT(), parseE2())

  def parseE2(): Option[E2] = {
    if (index < input.length && input(index) == '|') {
      C(input(index))
      index += 1;
      Some(E2(parseE3()))
    }
    else None
  }

  def parseT(): T = T(parseF(), parseT2())

  def parseE3(): E3 = E3(parseT(), parseE2())

  def parseT2(): Option[T2] = {
    if (index < input.length && (input(index).isLetterOrDigit ||  input(index) == '.' ||   input(index) == '(' ||  input(index) == ' ')) {

      Some(T2(parseF(), parseT2()))
    }

    else

      None
  }

  def parseF(): F = F(parseA(), parseF2())


  def parseF2(): Option[F2] = {
    if (index < input.length && input(index) == '?') {
      index += 1;
      Some(F2(parseF2()))
    }
    else None
  }

  def parseA2(): A2 = {


    val a2 = A2(parseE())
if (index < input.length &&  input(index) == ')')
index +=1
  a2
  }



  def parseA(): A= {


    if (index < input.length && (input(index).isLetterOrDigit ||  input(index) == '.' ||  input(index) == ' ')) {
      val currChar = input.charAt(index)
      index += 1

      C(currChar)


  }else {
    index+=1
    parseA2()}
  }
}

object Main {
  def main(args: Array[String]): Unit ={

    val pattern = scala.io.StdIn.readLine("Enter Pattern: ")
    val newRecusive= new RecursiveDescent(pattern)
    val Mtree: S = newRecusive.parseE()
    println(Mtree)
    while(true){
      var string = scala.io.StdIn.readLine("Enter String: ")
      if (Mtree.eval(string)) {
        if (count.countIndex < string.length) {
          println("no match")
        } else {
          println("match")
        }
      }else{
        println("no match")
      }
      count.countIndex = 0
    }
  }
}
