package idea.adapters.gui;


import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

import org.jfree.data.time.Day;
import org.jfree.data.time.Hour;
import org.jfree.data.time.RegularTimePeriod;

/**
 * Represents a minute.  This class is immutable, which is a requirement for
 * all {@link RegularTimePeriod} subclasses.
 */
public class NMinute extends RegularTimePeriod implements Serializable {

    /** For serialization. */
    private static final long serialVersionUID = 2144572840034842871L;

    /** Useful constant for the first minute in a day. */
    public static final int FIRST_MINUTE_IN_HOUR = 0;

    /** Useful constant for the last minute in a day. */
    public static final int LAST_MINUTE_IN_HOUR = 59;

    /** The day. */
    private Day day;

    /** The hour in which the minute falls. */
    private byte hour;

    /** The minute. */
    private byte minute;

    /** The first millisecond. */
    private long firstMillisecond;

    /** The last millisecond. */
    private long lastMillisecond;

	private int n_min;

    /**
     * Constructs a new Minute, based on the system date/time.
     */
    public NMinute( int n_min ) {
        this(new Date(), n_min);
    }

    /**
     * Constructs a new Minute.
     *
     * @param minute  the minute (0 to 59).
     * @param hour  the hour (<code>null</code> not permitted).
     */
    public NMinute(int minute, Hour hour, int n_min) {
        if (hour == null) {
            throw new IllegalArgumentException("Null 'hour' argument.");
        }
        this.minute = (byte) minute;
        this.hour = (byte) hour.getHour();
        this.day = hour.getDay();
        this.n_min = n_min;
        peg(Calendar.getInstance());
    }

    /**
     * Constructs a new instance, based on the supplied date/time and
     * the default time zone.
     *
     * @param time  the time (<code>null</code> not permitted).
     *
     * @see #Minute(Date, TimeZone)
     */
    public NMinute(Date time, int n_min ) {
        // defer argument checking
        this(time, TimeZone.getDefault(), Locale.getDefault(), n_min);
    }

    /**
     * Constructs a new Minute, based on the supplied date/time and timezone.
     *
     * @param time  the time (<code>null</code> not permitted).
     * @param zone  the time zone (<code>null</code> not permitted).
     *
     * @deprecated As of 1.0.13, use the constructor that specifies the locale
     *     also.
     */
    public NMinute(Date time, TimeZone zone, int n_min) {
        this(time, zone, Locale.getDefault(), n_min );
    }

    /**
     * Constructs a new Minute, based on the supplied date/time and timezone.
     *
     * @param time  the time (<code>null</code> not permitted).
     * @param zone  the time zone (<code>null</code> not permitted).
     * @param locale  the locale (<code>null</code> not permitted).
     *
     * @since 1.0.13
     */
    public NMinute(Date time, TimeZone zone, Locale locale, int n_min) {
        if (time == null) {
            throw new IllegalArgumentException("Null 'time' argument.");
        }
        if (zone == null) {
            throw new IllegalArgumentException("Null 'zone' argument.");
        }
        if (locale == null) {
            throw new IllegalArgumentException("Null 'locale' argument.");
        }
        Calendar calendar = Calendar.getInstance(zone, locale);
        calendar.setTime(time);
        int min = calendar.get(Calendar.MINUTE);
        this.minute = (byte) min;
        this.hour = (byte) calendar.get(Calendar.HOUR_OF_DAY);
        this.day = new Day(time, zone, locale);
        this.n_min = n_min;
        peg(calendar);
    }

    /**
     * Returns the day.
     *
     * @return The day.
     *
     * @since 1.0.3
     */
    public Day getDay() {
        return this.day;
    }

    /**
     * Returns the hour.
     *
     * @return The hour (never <code>null</code>).
     */
    public Hour getHour() {
        return new Hour(this.hour, this.day);
    }

    /**
     * Returns the hour.
     *
     * @return The hour.
     *
     * @since 1.0.3
     */
    public int getHourValue() {
        return this.hour;
    }

    /**
     * Returns the minute.
     *
     * @return The minute.
     */
    public int getMinute() {
        return this.minute;
    }

    /**
     * Returns the first millisecond of the minute.  This will be determined
     * relative to the time zone specified in the constructor, or in the
     * calendar instance passed in the most recent call to the
     * {@link #peg(Calendar)} method.
     *
     * @return The first millisecond of the minute.
     *
     * @see #getLastMillisecond()
     */
    public long getFirstMillisecond() {
        return this.firstMillisecond;
    }

    /**
     * Returns the last millisecond of the minute.  This will be
     * determined relative to the time zone specified in the constructor, or
     * in the calendar instance passed in the most recent call to the
     * {@link #peg(Calendar)} method.
     *
     * @return The last millisecond of the minute.
     *
     * @see #getFirstMillisecond()
     */
    public long getLastMillisecond() {
        return this.lastMillisecond;
    }

    /**
     * Recalculates the start date/time and end date/time for this time period
     * relative to the supplied calendar (which incorporates a time zone).
     *
     * @param calendar  the calendar (<code>null</code> not permitted).
     *
     * @since 1.0.3
     */
    public void peg(Calendar calendar) {
        this.firstMillisecond = getFirstMillisecond(calendar);
        this.lastMillisecond = getLastMillisecond(calendar);
    }

    /**
     * Returns the minute preceding this one.
     *
     * @return The minute preceding this one.
     */
    public RegularTimePeriod previous() {
        NMinute result;
        if (this.minute != FIRST_MINUTE_IN_HOUR) {
            result = new NMinute(this.minute - 1, getHour(), n_min);
        }
        else {
            Hour h = (Hour) getHour().previous();
            if (h != null) {
                result = new NMinute(LAST_MINUTE_IN_HOUR, h, n_min);
            }
            else {
                result = null;
            }
        }
        return result;
    }

    /**
     * Returns the minute following this one.
     *
     * @return The minute following this one.
     */
    public RegularTimePeriod next() {
    	NMinute result;
        if (this.minute != LAST_MINUTE_IN_HOUR) {
            result = new NMinute(this.minute + n_min, getHour(), n_min);
        }
        else { // we are at the last minute in the hour...
            Hour nextHour = (Hour) getHour().next();
            if (nextHour != null) {
                result = new NMinute(FIRST_MINUTE_IN_HOUR, nextHour, n_min);
            }
            else {
                result = null;
            }
        }
        return result;
    }

    /**
     * Returns a serial index number for the minute.
     *
     * @return The serial index number.
     */
    public long getSerialIndex() {
        long hourIndex = this.day.getSerialIndex() * 24L + this.hour;
        return hourIndex * 60L + this.minute;
    }

    /**
     * Returns the first millisecond of the minute.
     *
     * @param calendar  the calendar which defines the timezone
     *     (<code>null</code> not permitted).
     *
     * @return The first millisecond.
     *
     * @throws NullPointerException if <code>calendar</code> is
     *     <code>null</code>.
     */
    public long getFirstMillisecond(Calendar calendar) {
        int year = this.day.getYear();
        int month = this.day.getMonth() - 1;
        int day = this.day.getDayOfMonth();

        calendar.clear();
        calendar.set(year, month, day, this.hour, this.minute, 0);
        calendar.set(Calendar.MILLISECOND, 0);

        //return calendar.getTimeInMillis();  // this won't work for JDK 1.3
        return calendar.getTime().getTime();
    }

    /**
     * Returns the last millisecond of the minute.
     *
     * @param calendar  the calendar / timezone (<code>null</code> not
     *     permitted).
     *
     * @return The last millisecond.
     *
     * @throws NullPointerException if <code>calendar</code> is
     *     <code>null</code>.
     */
    public long getLastMillisecond(Calendar calendar) {
        int year = this.day.getYear();
        int month = this.day.getMonth() - 1;
        int day = this.day.getDayOfMonth();

        calendar.clear();
        calendar.set( year, month, day, this.hour, this.minute, 59);
        calendar.set(Calendar.MILLISECOND, 999);
        //long dbg = calendar.getTime().getTime();
        calendar.add( Calendar.MINUTE, n_min - 1);
        
        long lastMs = calendar.getTime().getTime();
        
        //System.out.println( "nmin=" + n_min + " dbg="+ (getFirstMillisecond() - dbg) + " lasms gap=" + (getFirstMillisecond() - lastMs));

        //return calendar.getTimeInMillis();  // this won't work for JDK 1.3
        return lastMs;
    }

    /**
     * Tests the equality of this object against an arbitrary Object.
     * <P>
     * This method will return true ONLY if the object is a Minute object
     * representing the same minute as this instance.
     *
     * @param obj  the object to compare (<code>null</code> permitted).
     *
     * @return <code>true</code> if the minute and hour value of this and the
     *      object are the same.
     */
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }
        if (!(obj instanceof NMinute)) {
            return false;
        }
        NMinute that = (NMinute) obj;
        if (this.minute != that.minute) {
            return false;
        }
        if (this.hour != that.hour) {
            return false;
        }
        return true;
    }

    /**
     * Returns a hash code for this object instance.  The approach described
     * by Joshua Bloch in "Effective Java" has been used here:
     * <p>
     * <code>http://developer.java.sun.com/developer/Books/effectivejava
     * /Chapter3.pdf</code>
     *
     * @return A hash code.
     */
    public int hashCode() {
        int result = 17;
        result = 37 * result + this.minute;
        result = 37 * result + this.hour;
        result = 37 * result + this.day.hashCode();
        return result;
    }

    /**
     * Returns an integer indicating the order of this Minute object relative
     * to the specified object:
     *
     * negative == before, zero == same, positive == after.
     *
     * @param o1  object to compare.
     *
     * @return negative == before, zero == same, positive == after.
     */
    public int compareTo(Object o1) {
        int result;

        // CASE 1 : Comparing to another Minute object
        // -------------------------------------------
        if (o1 instanceof NMinute) {
        	NMinute m = (NMinute) o1;
            result = getHour().compareTo(m.getHour());
            if (result == 0) {
                result = this.minute - m.getMinute();
            }
        }

        // CASE 2 : Comparing to another TimePeriod object
        // -----------------------------------------------
        else if (o1 instanceof RegularTimePeriod) {
            // more difficult case - evaluate later...
            result = 0;
        }

        // CASE 3 : Comparing to a non-TimePeriod object
        // ---------------------------------------------
        else {
            // consider time periods to be ordered after general objects
            result = 1;
        }

        return result;
    }


}
