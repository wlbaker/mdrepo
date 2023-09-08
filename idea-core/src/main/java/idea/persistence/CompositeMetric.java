package idea.persistence;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface CompositeMetric {

	String loc();

	String code() default "";

	String desc() default "";

	int max_count() default 1;

	// public abstract Metric[] value();
}
