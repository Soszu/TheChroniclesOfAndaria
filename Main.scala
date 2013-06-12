object Main {

  def flatten(list: List[List[_]]): List[_] = 
    list match {
    case h::t => h:::flatten(t)
    case Nil => Nil 
  }  
  
  def rev[A](list: List[A]): List[A] = {
    
    def pom[A](list: List[A], acc: List[A]): List[A] =
    	list match {
    		case h::t => pom[A](t, h::acc)
    		case Nil => acc
    }
    
    pom(list, Nil)
  } 
  
  def flatten2[A](list: List[List[A]]): List[A] = {
    
    def pom[A](l: List[List[A]], acc: List[A]): List[A] = 
      l match {
      	case lists_head::lists_tail => 
      		lists_head match {
      			case head::tail => pom[A](tail::lists_tail, head::acc)
      			case Nil => pom[A](lists_tail, acc)
      		}
      	case Nil => rev(acc)
    }
    pom[A](list, Nil)
  }
  
  def flatten3(list: List[List[_]]): List[_] =
    for{ xs <- list; x <- xs} yield x  
  
  def main(args: Array[String]): Unit = {
    
    var l1 = List(2,3,4,5,6)
    var l2 = List(1,1,1,1,2,3)
    var l3 = List("qeq","af", "rr")
    
    println(flatten(List(l1,l2,l3)))
    println(flatten2(List(l1,l2,l3)))
    println(flatten3(List(l1,l2,l3)))
    
    
  }

}