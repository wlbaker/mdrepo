package idea.schema.rp;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import javax.xml.bind.DatatypeConverter;

public class DateTimeAdapter {
  public static Date parseDate(String s) {
    return DatatypeConverter.parseDateTime(s).getTime();
  }
  public static String printDate(Date dt) {
    Calendar cal = new GregorianCalendar();
    cal.setTime(dt);
    return DatatypeConverter.printDateTime(cal);
  }
}

