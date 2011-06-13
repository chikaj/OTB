/*
 * Example on the use of the Smoothing 
 */
 
import org.otb.application.*;


class SmoothingTest {

  public static void main( String argv[] ) {

    System.out.println( "Available applications : " + Registry.GetAvailableApplications() );

    Application_Pointer app = Registry.CreateApplication("Smoothing");
    
    System.out.println( Registry.CreateApplication("Smoothing").GetDescription() );
    
  }

}