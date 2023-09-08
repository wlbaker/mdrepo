

--- Simple versioning mechanism:
--- For all schema changes, update the version string below which is
--- formatted as year.month.day.version (version starts with 01 for day)
--- schema version 16.10.25.01
DROP DATABASE IF EXISTS mp70db;
CREATE DATABASE mp70db WITH TEMPLATE = template0 ENCODING = 'UTF8';
\connect mp70db;

--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: alarms; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE alarms (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    type_partition integer DEFAULT 0 NOT NULL,
    type_code smallint DEFAULT 0 NOT NULL,
    alarm_source smallint DEFAULT 0 NOT NULL,
    context_seq_number character varying(255) DEFAULT '0'::character varying NOT NULL,
    event_message character varying(255) DEFAULT ''::character varying NOT NULL,
    initial_priority integer DEFAULT 0 NOT NULL,
    latch integer DEFAULT 0 NOT NULL,
    alarm_condition_seconds bigint DEFAULT 0 NOT NULL,
    alarm_signal_generation_delay bigint DEFAULT 0 NOT NULL,
    alarm_signal_inactivation_state integer DEFAULT 0 NOT NULL,
    auditory_alarm_signal_set_tbd bigint DEFAULT 0 NOT NULL,
    alarm_paused_seconds bigint DEFAULT 0 NOT NULL,
    audio_paused_seconds bigint DEFAULT 0 NOT NULL,
    alarm_acknowledge_seconds bigint DEFAULT 0 NOT NULL,
    alarm_condition_type integer DEFAULT 1 NOT NULL,
    alarm_condition_limit_type integer DEFAULT 0 NOT NULL,
    alarm_condition_limit_value character varying(255) DEFAULT '0'::character varying NOT NULL,
    alarm_condition_alarm_code smallint DEFAULT 0 NOT NULL,
    alarm_condition_unit_code smallint DEFAULT 0 NOT NULL,
    alarm_parameters smallint,
    alarm_preset_list_tbd bigint DEFAULT 0 NOT NULL,
    escalation_list_type integer,
    escalation_list_path integer,
    visual_alarm_characteristics_type integer DEFAULT 0 NOT NULL,
    auditory_reminder_signal_seconds bigint DEFAULT 0 NOT NULL,
    auditory_alarm_signal_db bigint DEFAULT 0 NOT NULL,
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.alarms OWNER TO postgres;

--
-- Name: alarms_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE alarms_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.alarms_id_seq OWNER TO postgres;

--
-- Name: alarms_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE alarms_id_seq OWNED BY alarms.id;


--
-- Name: enum_contexts; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE enum_contexts (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    type_partition integer DEFAULT 0 NOT NULL,
    type_code smallint DEFAULT 0 NOT NULL,
    context_seq_number character varying(255) DEFAULT '0'::character varying NOT NULL,
    metric_specification_update_period_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    metric_specification_update_period_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    metric_specification_category integer DEFAULT 0 NOT NULL,
    metric_specification_access smallint DEFAULT 0 NOT NULL,
    metric_specification_relevance smallint DEFAULT 0 NOT NULL,
    max_delay_time_seconds character varying(255),
    max_delay_time_nanoseconds character varying(255),
    vmo_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    vmo_source_list_vmo_type smallint,
    vmo_source_list_glb_handle_context_id smallint,
    vmo_source_list_glb_handle_handle smallint,
    metric_source_list smallint,
    unit_code smallint DEFAULT 0 NOT NULL,
    unit_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    msmt_site_list smallint,
    body_site_list smallint,
    metric_status smallint DEFAULT 0 NOT NULL,
    measure_period_value double precision,
    measure_period_unit_code smallint,
    averaging_period_value double precision,
    averaging_period_unit_code smallint,
    start_time_seconds character varying(255),
    start_time_nanoseconds character varying(255),
    stop_time_seconds character varying(255),
    stop_time_nanoseconds character varying(255),
    metric_calibration_cal_type integer,
    metric_calibration_cal_state integer,
    metric_calibration_cal_time_seconds character varying(255),
    metric_calibration_cal_time_nanoseconds character varying(255),
    color integer,
    measurement_status smallint DEFAULT 0 NOT NULL,
    metric_id smallint DEFAULT 0 NOT NULL,
    metric_info_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    substance_nomenclature_id smallint,
    substance_nomenclature_code character varying(255),
    substance_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    enum_measure_range smallint,
    enum_measure_range_bits bigint,
    enum_measure_range_labels_value integer,
    enum_measure_range_labels_label character varying(255),
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.enum_contexts OWNER TO postgres;

--
-- Name: enum_contexts_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE enum_contexts_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.enum_contexts_id_seq OWNER TO postgres;

--
-- Name: enum_contexts_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE enum_contexts_id_seq OWNED BY enum_contexts.id;


--
-- Name: mds; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE mds (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    system_type_partition integer DEFAULT 0 NOT NULL,
    system_type_code smallint DEFAULT 0 NOT NULL,
    system_model_manufacturer character varying(255) DEFAULT ''::character varying NOT NULL,
    system_model_model_number character varying(255) DEFAULT ''::character varying NOT NULL,
    nomenclature_version_nom_major_version smallint DEFAULT 0 NOT NULL,
    nomenclature_version_nom_minor_version smallint DEFAULT 0 NOT NULL,
    system_capability bigint DEFAULT 0 NOT NULL,
    system_specification_component_capab_id smallint,
    system_specification_component_spec character varying(255),
    production_specification_spec_type integer,
    production_specification_component_id smallint,
    production_specification_prod_spec character varying(255),
    mds_status integer DEFAULT 0 NOT NULL,
    operating_mode smallint,
    date_and_time_seconds character varying(255),
    date_and_time_nanoseconds character varying(255),
    relative_time_seconds character varying(255),
    relative_time_nanoseconds character varying(255),
    power_status smallint,
    battery_level smallint,
    remaining_battery_minutes smallint,
    altitude_meters smallint,
    line_frequency integer,
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.mds OWNER TO postgres;

--
-- Name: mds_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE mds_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.mds_id_seq OWNER TO postgres;

--
-- Name: mds_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE mds_id_seq OWNED BY mds.id;


--
-- Name: mp70db_version; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE mp70db_version (
    id integer NOT NULL,
    version character varying(32)
);


ALTER TABLE public.mp70db_version OWNER TO postgres;

--
-- Name: mp70db_version_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE mp70db_version_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.mp70db_version_id_seq OWNER TO postgres;

--
-- Name: mp70db_version_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE mp70db_version_id_seq OWNED BY mp70db_version.id;


--
-- Name: numeric_contexts; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE numeric_contexts (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id bigint,
    context_id smallint DEFAULT 0 NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    type_partition integer DEFAULT 0 NOT NULL,
    type_code smallint DEFAULT 0 NOT NULL,
    metric_specification_update_period_seconds bigint DEFAULT 0 NOT NULL,
    metric_specification_update_period_nanoseconds bigint DEFAULT 0 NOT NULL,
    metric_specification_access smallint DEFAULT 0 NOT NULL,
    metric_specification_relevance smallint DEFAULT 0 NOT NULL,
    max_delay_time_seconds bigint,
    max_delay_time_nanoseconds bigint,
    vmo_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    vmo_source_list_vmo_type smallint,
    vmo_source_list_glb_handle_context_id smallint,
    vmo_source_list_glb_handle_handle smallint,
    metric_source_list smallint,
    unit_code smallint DEFAULT 0 NOT NULL,
    unit_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    msmt_site_list smallint,
    body_site_list smallint,
    metric_status smallint DEFAULT 0 NOT NULL,
    measure_period_value double precision,
    measure_period_unit_code smallint,
    averaging_period_value double precision,
    averaging_period_unit_code smallint,
    start_time_seconds bigint,
    start_time_nanoseconds bigint,
    stop_time_seconds bigint,
    stop_time_nanoseconds bigint,
    metric_calibration_cal_type integer,
    metric_calibration_cal_state integer,
    metric_calibration_cal_time_seconds bigint,
    metric_calibration_cal_time_nanoseconds bigint,
    color integer,
    measurement_status smallint DEFAULT 0 NOT NULL,
    metric_id bigint DEFAULT 0 NOT NULL,
    metric_info_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    substance_nomenclature_id smallint,
    substance_nomenclature_code character varying(255),
    substance_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    nu_measure_range_lower_value double precision,
    nu_measure_range_upper_value double precision,
    nu_physiological_range_lower_value double precision,
    nu_physiological_range_upper_value double precision,
    display_resolution_pre_point bytea,
    display_resolution_post_point bytea,
    accuracy double precision,
    created_at timestamp without time zone,
    updated_at timestamp without time zone,
    source_timestamp_seconds integer DEFAULT 0 NOT NULL,
    source_timestamp_nanoseconds integer DEFAULT 0 NOT NULL,
    context_seq_number integer DEFAULT 0 NOT NULL,
    metric_specification_category integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.numeric_contexts OWNER TO postgres;

--
-- Name: numeric_contexts_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE numeric_contexts_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.numeric_contexts_id_seq OWNER TO postgres;

--
-- Name: numeric_contexts_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE numeric_contexts_id_seq OWNED BY numeric_contexts.id;


--
-- Name: pat_demo_reqs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE pat_demo_reqs (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    sex integer,
    gender integer,
    race_race_type integer,
    race_provenance character varying(255),
    patient_type integer,
    chronological_age_value double precision,
    chronological_age_m_unit smallint,
    patient_height_value double precision,
    patient_height_m_unit smallint,
    patient_weight_value double precision,
    patient_weight_m_unit smallint,
    neonatal_gestational_age_value double precision,
    neonatal_gestational_age_m_unit smallint,
    neonatal_patient_birth_length_value double precision,
    neonatal_patient_birth_length_m_unit smallint,
    neonatal_patient_birth_weight_value double precision,
    neonatal_patient_birth_weight_m_unit smallint,
    neonatal_patient_head_circumference_value double precision,
    neonatal_patient_head_circumference_m_unit smallint,
    neonatal_mother_patient_id_given_name character varying(255),
    neonatal_mother_patient_id_family_name character varying(255),
    neonatal_mother_patient_id_middle_name character varying(255),
    neonatal_mother_patient_id_date_of_birth_century bytea,
    neonatal_mother_patient_id_date_of_birth_year bytea,
    neonatal_mother_patient_id_date_of_birth_month bytea,
    neonatal_mother_patient_id_date_of_birth_day bytea,
    neonatal_mother_patient_id_patient_id character varying(255),
    neonatal_mother_patient_id_patient_id_provenance character varying(255),
    neonatal_mother_patient_id_verified boolean,
    neonatal_mother_patient_id_pat_admit_state integer,
    neonatal_mother_patient_id_pat_episode_id smallint,
    neonatal_mother_patient_id_episode_start_seconds character varying(255),
    neonatal_mother_patient_id_episode_start_nanoseconds character varying(255),
    neonatal_mother_name character varying(255),
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.pat_demo_reqs OWNER TO postgres;

--
-- Name: pat_demos_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE pat_demos_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.pat_demos_id_seq OWNER TO postgres;

--
-- Name: pat_demos_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE pat_demos_id_seq OWNED BY pat_demo_reqs.id;


--
-- Name: pat_ident_reqs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE pat_ident_reqs (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    given_name character varying(255) DEFAULT ''::character varying NOT NULL,
    family_name character varying(255) DEFAULT ''::character varying NOT NULL,
    middle_name character varying(255) DEFAULT ''::character varying NOT NULL,
    date_of_birth_century bytea,
    date_of_birth_year bytea,
    date_of_birth_month bytea,
    date_of_birth_day bytea,
    patient_id character varying(255) DEFAULT ''::character varying,
    patient_id_provenance character varying(255),
    verified boolean DEFAULT false NOT NULL,
    pat_admit_state integer DEFAULT 0 NOT NULL,
    pat_episode_id smallint DEFAULT 0 NOT NULL,
    episode_start_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    episode_start_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.pat_ident_reqs OWNER TO postgres;

--
-- Name: pat_idents_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE pat_idents_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.pat_idents_id_seq OWNER TO postgres;

--
-- Name: pat_idents_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE pat_idents_id_seq OWNED BY pat_ident_reqs.id;


--
-- Name: sample_array_contexts; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sample_array_contexts (
    id integer NOT NULL,
    instance_name character varying(255) DEFAULT ''::character varying NOT NULL,
    context_id smallint DEFAULT 0 NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    type_partition integer DEFAULT 0 NOT NULL,
    type_code smallint DEFAULT 0 NOT NULL,
    metric_specification_update_period_seconds bigint DEFAULT 0 NOT NULL,
    metric_specification_update_period_nanoseconds bigint DEFAULT 0 NOT NULL,
    metric_specification_access smallint DEFAULT 0 NOT NULL,
    metric_specification_relevance smallint DEFAULT 0 NOT NULL,
    max_delay_time_seconds bigint,
    max_delay_time_nanoseconds bigint,
    vmo_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    vmo_source_list_vmo_type smallint,
    vmo_source_list_glb_handle_context_id smallint,
    vmo_source_list_glb_handle_handle smallint,
    metric_source_list smallint,
    unit_code smallint DEFAULT 0 NOT NULL,
    unit_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    msmt_site_list smallint,
    body_site_list smallint,
    metric_status smallint DEFAULT 0 NOT NULL,
    measure_period_value double precision,
    measure_period_unit_code smallint,
    averaging_period_value double precision,
    averaging_period_unit_code smallint,
    start_time_seconds bigint,
    start_time_nanoseconds bigint,
    stop_time_seconds bigint,
    stop_time_nanoseconds bigint,
    metric_calibration_cal_type integer,
    metric_calibration_cal_state integer,
    metric_calibration_cal_time_seconds bigint,
    metric_calibration_cal_time_nanoseconds bigint,
    color integer,
    measurement_status smallint DEFAULT 0 NOT NULL,
    metric_id smallint DEFAULT 0 NOT NULL,
    metric_info_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    substance_nomenclature_id smallint,
    substance_nomenclature_code character varying(255),
    substance_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    sa_specification_array_size smallint DEFAULT 0 NOT NULL,
    sa_specification_sample_type_sample_size bytea,
    sa_specification_sample_type_significant_bits bytea,
    sa_specification_sample_type_signed_samples bytea,
    sa_specification_flags smallint DEFAULT 0 NOT NULL,
    compression smallint,
    sa_marker_list_marker_id smallint,
    sa_marker_list_marker_val bigint,
    scale_and_range_specification_lower_absolute_value double precision DEFAULT 0 NOT NULL,
    scale_and_range_specification_upper_absolute_value double precision DEFAULT 0 NOT NULL,
    scale_and_range_specification_lower_scaled_value bigint DEFAULT 0 NOT NULL,
    scale_and_range_specification_upper_scaled_value bigint DEFAULT 0 NOT NULL,
    sa_physiological_range_lower_scaled_value bigint,
    sa_physiological_range_upper_scaled_value bigint,
    visual_grid_absolute_value double precision,
    visual_grid_scaled_value bigint,
    visual_grid_level smallint,
    sa_calibration_data_lower_absolute_value double precision,
    sa_calibration_data_upper_absolute_value double precision,
    sa_calibration_data_lower_scaled_value bigint,
    sa_calibration_data_upper_scaled_value bigint,
    sa_calibration_data_increment bigint,
    sa_calibration_data_cal_type integer,
    filter_specification_filter_type integer,
    filter_specification_filter_frequency double precision,
    filter_specification_filter_order smallint,
    filter_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    sa_signal_frequencey_low_edge_freq double precision,
    sa_signal_frequencey_high_edge_freq double precision,
    sa_measure_resolution double precision,
    sample_period_seconds bigint DEFAULT 0 NOT NULL,
    sample_period_nanoseconds bigint DEFAULT 0 NOT NULL,
    sweep_speed_value double precision,
    sweep_speed_unit_code smallint,
    average_reporting_delay_seconds bigint,
    average_reporting_delay_nanoseconds bigint,
    sample_time_sync_seconds bigint,
    sample_time_sync_nanoseconds bigint,
    created_at timestamp without time zone,
    updated_at timestamp without time zone,
    ice_id integer,
    source_timestamp_nanoseconds integer DEFAULT 0 NOT NULL,
    source_timestamp_seconds integer DEFAULT 0 NOT NULL,
    context_seq_number integer DEFAULT 0 NOT NULL,
    metric_specification_category integer DEFAULT 0 NOT NULL,
    sa_signal_frequency_low_edge_freq integer,
    sa_signal_frequency_high_edge_freq integer
);


ALTER TABLE public.sample_array_contexts OWNER TO postgres;

--
-- Name: sample_array_contexts_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sample_array_contexts_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.sample_array_contexts_id_seq OWNER TO postgres;

--
-- Name: sample_array_contexts_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sample_array_contexts_id_seq OWNED BY sample_array_contexts.id;


--
-- Name: schema_migrations; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE schema_migrations (
    version character varying(255) NOT NULL
);


ALTER TABLE public.schema_migrations OWNER TO postgres;

--
-- Name: table_versions; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE table_versions (
    id integer NOT NULL,
    name double precision,
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.table_versions OWNER TO postgres;

--
-- Name: table_versions_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE table_versions_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.table_versions_id_seq OWNER TO postgres;

--
-- Name: table_versions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE table_versions_id_seq OWNED BY table_versions.id;


--
-- Name: vmds; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE vmds (
    id integer NOT NULL,
    instance_name character varying(255),
    ice_id character varying(255) DEFAULT ''::character varying NOT NULL,
    handle smallint DEFAULT 0 NOT NULL,
    parent_handle smallint DEFAULT 0 NOT NULL,
    source_timestamp_seconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    source_timestamp_nanoseconds character varying(255) DEFAULT '0'::character varying NOT NULL,
    type_partition integer DEFAULT 0 NOT NULL,
    type_code smallint DEFAULT 0 NOT NULL,
    instance_number smallint DEFAULT 0 NOT NULL,
    measurement_principle smallint,
    locale_language bigint DEFAULT 0 NOT NULL,
    locale_country bigint DEFAULT 0 NOT NULL,
    locale_charset integer DEFAULT 0 NOT NULL,
    locale_str_spec_str_max_len smallint DEFAULT 0 NOT NULL,
    locale_str_spec_str_flags smallint DEFAULT 0 NOT NULL,
    vmo_label_string character varying(255) DEFAULT ''::character varying NOT NULL,
    vmd_status smallint DEFAULT 0 NOT NULL,
    "position" smallint DEFAULT 0 NOT NULL,
    operating_hours bigint,
    operation_cycles bigint,
    vmd_model_manufacturer character varying(255) DEFAULT ''::character varying NOT NULL,
    vmd_model_model_number character varying(255) DEFAULT ''::character varying NOT NULL,
    production_specification_spec_type integer,
    production_specification_component_id smallint,
    production_specification_prod_spec character varying(255),
    created_at timestamp without time zone,
    updated_at timestamp without time zone
);


ALTER TABLE public.vmds OWNER TO postgres;

--
-- Name: vmds_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE vmds_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.vmds_id_seq OWNER TO postgres;

--
-- Name: vmds_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE vmds_id_seq OWNED BY vmds.id;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY alarms ALTER COLUMN id SET DEFAULT nextval('alarms_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY enum_contexts ALTER COLUMN id SET DEFAULT nextval('enum_contexts_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY mds ALTER COLUMN id SET DEFAULT nextval('mds_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY mp70db_version ALTER COLUMN id SET DEFAULT nextval('mp70db_version_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY numeric_contexts ALTER COLUMN id SET DEFAULT nextval('numeric_contexts_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY pat_demo_reqs ALTER COLUMN id SET DEFAULT nextval('pat_demos_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY pat_ident_reqs ALTER COLUMN id SET DEFAULT nextval('pat_idents_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sample_array_contexts ALTER COLUMN id SET DEFAULT nextval('sample_array_contexts_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY table_versions ALTER COLUMN id SET DEFAULT nextval('table_versions_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY vmds ALTER COLUMN id SET DEFAULT nextval('vmds_id_seq'::regclass);


--
-- Data for Name: alarms; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY alarms (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, type_partition, type_code, alarm_source, context_seq_number, event_message, initial_priority, latch, alarm_condition_seconds, alarm_signal_generation_delay, alarm_signal_inactivation_state, auditory_alarm_signal_set_tbd, alarm_paused_seconds, audio_paused_seconds, alarm_acknowledge_seconds, alarm_condition_type, alarm_condition_limit_type, alarm_condition_limit_value, alarm_condition_alarm_code, alarm_condition_unit_code, alarm_parameters, alarm_preset_list_tbd, escalation_list_type, escalation_list_path, visual_alarm_characteristics_type, auditory_reminder_signal_seconds, auditory_alarm_signal_db, created_at, updated_at) FROM stdin;
1595			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1596			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1597			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1598			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1599			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1600			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1601			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1602			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1603			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1604			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1605			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1606			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1607			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1608			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1609			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1610			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1611			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1612			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1613			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1614			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1615			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1616			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1617			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1618			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1619			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1620			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1621			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1622			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1623			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1624			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1625			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1626			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1627			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1628			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1629			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1630			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1631			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1632			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1633			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1634			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1635			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1636			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1637			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1638			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1639			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1640			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1641			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1642			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1643			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1644			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1645			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1646			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1647			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1648			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1649			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1650			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1651			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1652			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1653			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1654			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1655			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1656			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1657			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1658			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1659			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1660			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1661			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1662			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1663			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1664			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1665			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
882			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
883			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
884			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
885			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
886			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
887			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
888			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
889			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
890			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
891			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
892			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
893			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
894			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
895			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
896			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
897			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
898			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
899			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
900			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
901			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
902			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
903			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
904			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
905			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
906			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
907			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
908			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
909			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
910			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
911			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
912			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
913			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
914			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
915			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
916			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
917			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
918			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
919			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
920			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
921			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
922			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
923			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
924			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
925			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1666			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1667			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1668			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1669			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1670			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1671			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1672			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1673			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1674			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1675			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1676			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1677			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1678			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1679			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1680			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1681			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1682			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1683			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1684			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1685			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1686			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1687			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1688			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1689			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1690			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1691			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1692			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1693			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1694			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1695			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1696			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1697			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1698			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1699			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1700			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1701			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1702			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1703			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1704			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1705			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1706			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1707			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1708			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1709			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1710			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1711			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1712			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1713			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1714			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1715			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1716			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1717			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1718			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1719			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1720			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1721			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1722			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1723			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1724			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1725			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1726			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1727			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1728			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1729			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1730			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1731			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1732			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1733			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1734			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1735			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1736			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1737			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1738			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1739			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1740			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1741			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1742			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1743			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1744			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1745			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1746			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1747			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1748			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1749			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1750			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1751			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1752			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1753			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1754			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1755			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1756			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1757			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1758			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1759			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1760			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1761			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1762			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
2			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
3			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
4			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
5			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
6			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
7			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
8			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
9			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
10			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
11			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
12			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
13			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
14			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
15			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
16			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
17			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
18			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
19			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
20			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
21			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
22			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
23			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
24			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
25			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
26			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
27			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
28			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
29			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
30			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
31			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
32			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
33			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
34			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
35			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
36			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
37			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
38			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
39			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
40			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
41			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
42			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
43			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
44			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
45			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
46			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
47			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
48			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
49			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
50			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
51			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
52			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
53			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
54			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
55			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
56			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
57			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
58			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
59			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
60			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
61			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
62			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
63			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
64			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
65			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
66			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
67			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
68			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
69			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
70			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
71			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
72			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
73			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
74			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
75			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
76			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
77			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
78			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
79			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
80			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
81			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
82			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
83			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
84			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
85			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
86			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
87			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
88			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
89			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
90			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
91			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
92			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
93			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
94			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
95			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
96			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
97			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
98			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
99			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
100			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
101			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
102			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
103			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
104			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
105			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
106			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
107			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
108			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
109			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
110			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
111			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
112			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
113			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
114			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
115			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
116			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
117			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
118			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
119			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
120			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
121			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
122			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
123			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
124			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
125			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
126			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
127			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
128			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
129			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
130			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
131			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
132			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
133			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
134			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
135			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
136			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
137			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
138			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
139			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
140			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
141			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
142			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
143			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
144			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
145			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
146			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
147			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
148			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
149			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
150			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
151			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
152			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
153			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
154			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
155			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
156			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
157			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
158			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
159			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
160			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
161			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
162			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
163			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
164			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
165			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1535			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1536			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1537			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1538			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1539			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1540			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1541			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1542			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1543			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1544			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1545			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1546			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1547			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1548			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1549			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1550			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1551			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1552			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1553			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1554			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1555			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1556			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1557			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
166			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
167			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
186			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
187			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1510			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1511			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1512			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1513			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1514			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1515			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1516			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1519			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1520			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1521			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1522			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1523			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1524			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1525			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1526			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1527			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1528			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1529			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
168			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
169			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
170			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
171			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
172			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
173			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
174			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
175			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
176			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
177			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
178			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
179			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
180			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
181			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
182			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
183			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
184			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
185			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1517			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1518			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1530			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1531			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1532			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1533			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1534			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
188			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
189			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1485			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1505			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1506			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1507			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1508			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1509			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
190			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
191			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
192			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1474			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1475			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1476			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1477			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
194			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1480			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1481			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1482			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1483			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1484			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1430			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
201			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1429			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1455			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1456			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1457			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1486			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1487			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1488			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1489			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1490			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1491			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1492			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1493			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1494			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1495			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1496			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1497			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1498			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1499			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1500			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1501			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1502			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1503			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1504			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1478			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1479			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
193			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1458			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
202			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
203			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
204			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
205			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
206			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
229			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
230			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
231			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
232			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
233			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
237			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
238			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
239			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
240			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
241			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1434			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1435			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1436			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1437			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1438			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1439			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1440			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1441			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1442			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1443			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1444			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1445			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1446			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1447			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1448			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1449			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1450			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1466			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1467			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1468			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1469			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1451			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1452			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1453			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1454			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
234			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
235			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
236			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
195			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
196			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
197			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
198			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
199			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
200			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1459			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1460			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1461			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1462			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1463			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1464			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1465			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1470			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1471			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1472			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1473			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1431			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1432			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1433			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1396			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1397			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1398			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1399			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
242			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
243			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
247			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
248			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
249			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
250			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
251			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
207			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
208			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
209			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
210			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
211			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
212			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
213			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
214			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
215			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
216			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
217			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
218			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
222			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
223			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
224			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
225			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
226			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
227			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
228			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
244			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
245			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
288			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
289			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
290			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
307			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1403			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1405			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1406			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1407			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1408			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1409			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1410			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1411			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
219			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1400			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1401			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1402			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
277			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
278			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
279			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
280			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
281			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
282			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
283			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
284			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
285			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
286			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1404			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
287			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
220			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
221			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
246			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
306			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
311			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
312			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
265			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
266			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1412			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1413			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1414			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1415			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1416			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1417			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1418			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1419			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
267			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
268			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
269			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
270			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
271			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
272			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
273			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
274			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
275			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
276			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
252			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
253			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
254			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
255			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
256			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
257			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
258			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
259			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1374			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1375			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1376			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1377			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1378			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1379			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1420			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
308			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
318			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
319			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
320			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
321			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
322			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
323			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
324			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
325			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
260			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
261			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1392			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1393			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1394			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1395			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
340			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
341			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1354			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1355			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1356			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1357			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1358			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1359			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1360			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1361			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1362			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1371			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1372			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1373			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
309			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
310			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
313			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
314			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
315			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
316			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
317			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
326			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
327			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
328			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
329			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
330			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
331			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1421			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1422			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1423			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1319			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1320			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1424			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1425			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1380			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1381			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
351			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1426			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1427			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1428			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
262			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
263			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
264			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
291			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1321			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1322			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1323			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1324			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1325			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1326			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1327			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1328			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1382			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1383			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1384			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1385			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1386			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1387			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1388			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1389			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1390			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1391			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
342			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
343			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
347			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1316			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1317			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1345			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
388			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
389			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
390			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
391			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
392			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
393			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
394			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
395			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
396			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1346			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1347			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
292			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
293			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
294			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
295			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
296			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
297			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
298			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
299			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
300			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
301			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
302			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
303			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
304			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
305			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
332			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
333			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
334			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
335			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
336			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
337			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
338			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
339			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1363			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1364			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1365			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1366			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1367			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1368			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1369			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1370			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1318			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
348			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
349			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
350			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1329			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
344			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
345			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
346			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1352			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1353			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
376			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
377			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
378			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
379			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
380			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
381			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1330			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1331			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1332			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1338			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1339			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1340			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1348			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1349			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1350			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1351			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
415			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
416			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
417			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
382			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
383			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
384			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
385			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
386			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
387			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
397			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
398			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
399			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
400			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
401			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
402			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
403			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
404			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
405			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
406			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
407			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
408			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
409			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
410			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
411			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
412			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
413			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
414			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
418			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
419			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
353			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
354			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
355			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
356			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
357			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
358			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
359			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
360			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
361			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
362			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
363			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
364			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
365			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
366			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
367			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
368			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
369			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
370			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
371			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
372			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
373			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
374			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
375			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1307			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1308			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1309			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1310			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1311			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1312			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1313			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1314			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1315			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1333			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1334			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1335			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1336			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1337			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1227			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1228			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1229			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1230			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1231			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1232			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1233			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1234			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
420			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
421			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
422			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
352			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1341			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1342			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1343			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1344			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
445			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
446			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
447			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
454			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
455			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
434			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
435			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
436			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
437			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
438			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
439			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
440			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
441			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
442			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
443			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
444			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
456			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
457			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
458			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
459			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
460			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
461			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
462			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
448			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
449			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
450			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
451			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
452			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
453			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1239			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1240			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1241			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1242			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1243			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1244			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1245			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1246			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1237			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1238			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
423			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
424			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1259			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
463			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
464			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
465			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
466			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
467			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
468			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
469			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
470			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
471			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
472			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
473			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
474			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
475			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
476			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
477			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
478			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
479			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
480			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1260			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1235			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1236			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
425			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
426			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
427			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
428			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
429			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
430			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
431			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
432			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
433			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1261			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1262			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1263			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1264			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1265			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1266			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1267			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1268			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1269			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1270			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1271			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1272			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1273			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1274			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1275			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1276			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1283			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1284			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1285			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1286			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1287			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1288			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1289			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1290			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
481			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
482			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
483			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
484			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1222			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1223			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1224			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1178			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1179			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1180			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1181			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1182			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1183			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1184			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1185			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1186			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1187			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1188			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1189			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1190			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1191			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1136			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1137			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
485			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
486			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
487			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
488			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
489			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
490			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
491			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1201			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1202			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1203			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1204			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1205			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1206			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1207			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1138			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1139			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
927			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
928			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
929			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
930			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
931			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
932			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
933			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
934			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
935			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
936			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
937			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1291			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1292			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1293			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1294			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1295			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1296			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1297			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1298			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1299			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1300			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1301			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1302			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1303			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1304			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1305			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1306			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1208			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1209			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1277			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1278			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1279			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1280			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1281			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1282			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1210			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1211			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1212			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1213			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1214			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1247			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1248			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1249			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1250			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1251			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1252			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1253			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1254			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1255			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1256			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1257			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1258			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1215			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1216			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1217			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1218			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1219			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1220			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1221			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1103			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1104			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1105			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1106			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1107			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1108			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1109			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1110			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1111			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
522			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
523			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
524			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
505			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1116			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1117			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1118			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1119			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1120			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1121			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1122			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1130			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1131			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1132			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1140			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
506			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
507			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
508			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
509			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
510			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
511			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
492			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1175			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1176			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1177			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
497			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
498			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1101			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1102			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1112			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1113			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1114			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1115			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
512			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
513			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
514			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
515			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
516			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
517			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
518			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
519			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
520			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
521			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1072			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1073			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1095			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1096			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1097			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1098			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1099			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1071			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
997			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
998			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
999			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
539			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
540			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
541			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
542			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
543			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
544			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
545			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
546			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
547			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1141			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1142			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1143			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1144			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1145			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1074			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1075			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1076			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1077			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1078			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1079			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1080			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1081			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1082			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1083			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1084			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1085			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1086			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1087			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1088			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1146			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1147			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1148			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1149			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1150			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
493			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
494			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
495			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
496			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1225			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1226			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1151			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1152			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1153			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1154			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1155			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1156			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1157			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1158			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1159			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1160			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1161			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1162			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1163			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1164			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1165			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1166			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1167			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1168			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1169			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1170			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1171			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1172			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1173			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1174			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1192			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1193			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1194			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1195			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1196			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1197			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1198			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1199			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1200			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1133			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1134			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1135			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1100			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1123			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1124			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1125			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1126			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1127			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
551			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
552			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
553			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
554			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
555			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
556			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
525			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
526			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
527			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
528			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1128			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1129			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
959			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
853			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
854			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
855			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
856			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
857			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
858			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
586			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
548			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
549			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
550			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
938			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
939			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
499			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
500			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
501			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
502			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
503			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
504			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
940			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
941			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
942			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
943			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
944			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
945			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
946			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
947			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
948			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
949			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
950			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
951			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
960			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
961			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
962			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
963			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
964			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
965			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
966			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1000			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
581			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
582			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
583			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
584			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
585			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
688			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
689			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
690			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
691			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
692			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
693			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
694			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
695			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
696			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
697			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
698			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
699			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
700			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
701			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1028			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1029			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1030			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1031			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1032			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1033			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
978			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
979			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
980			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
981			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
982			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
983			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
984			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
557			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
558			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
559			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
560			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
561			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
562			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
563			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
564			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
565			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
566			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
567			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
568			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
569			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
570			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1089			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1090			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1091			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1092			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1093			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1094			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
571			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
572			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1040			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1041			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1048			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1049			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1050			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1051			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1052			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1053			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1054			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1055			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1056			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1057			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1058			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1059			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1060			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1061			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1062			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1063			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1064			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1065			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1066			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1067			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1068			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1069			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
529			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
530			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
531			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
532			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1043			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1044			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1045			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1046			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1047			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
587			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
588			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
589			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
590			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
591			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1070			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
992			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
993			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
533			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
534			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
535			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
536			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1042			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
994			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
995			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
996			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1001			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1002			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1003			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1004			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1005			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1006			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1034			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1035			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1036			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
967			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
968			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
969			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
970			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
971			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
972			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
973			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
974			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
975			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
976			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
977			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1011			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1012			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1013			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1014			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1015			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1016			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1017			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1018			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1019			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1020			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1021			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1022			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1023			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1024			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1025			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1026			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
573			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
574			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
575			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1037			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1038			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1039			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1027			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
956			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
957			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
958			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
647			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
648			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
649			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
650			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
651			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
652			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
653			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
654			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
655			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
656			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
657			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
658			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
659			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
660			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
661			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
662			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
663			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
664			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
665			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
666			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
667			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
668			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
669			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
670			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
671			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
672			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
673			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
674			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
675			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
676			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
677			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
678			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
679			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
680			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
681			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1007			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1008			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1009			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1010			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
682			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
683			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
684			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
685			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
686			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
687			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
702			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
703			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
704			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
705			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
706			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
707			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
708			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
709			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
710			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
711			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
712			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
713			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
714			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
715			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
716			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
727			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
728			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
733			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
537			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
538			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
576			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
577			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
578			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
579			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
580			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
926			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
952			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
953			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
954			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
955			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
985			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
986			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
987			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
988			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
989			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
990			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
991			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
734			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
735			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
592			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
593			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
594			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
595			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
596			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
613			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
614			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
615			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
616			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
617			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
717			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
718			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
719			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
720			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
721			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
618			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
619			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
620			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
621			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
622			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
736			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
737			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
738			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
739			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
740			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
741			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
742			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
743			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
744			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
745			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
746			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
747			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
847			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
848			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
729			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
730			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
731			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
732			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
849			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
850			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
851			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
852			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
722			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
723			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
724			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
725			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
726			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
783			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
784			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
785			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
786			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
787			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
788			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
789			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
790			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
791			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
792			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
793			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
794			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
795			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
796			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
797			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
798			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
865			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
866			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
867			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
868			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
869			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
597			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
598			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
599			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
600			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
601			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
602			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
603			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
604			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
605			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
606			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
607			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
608			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
609			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
610			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
611			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
612			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
870			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
871			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
872			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
873			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
874			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
875			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
876			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
877			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
878			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
879			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
880			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
881			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
626			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
627			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
628			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
629			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
630			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
631			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
632			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
633			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
634			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
635			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
636			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
637			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
638			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
639			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
799			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
800			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
801			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
802			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
803			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
804			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
805			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
806			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
807			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
808			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
809			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
810			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
811			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
812			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
813			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
814			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
815			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
816			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
817			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
818			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
623			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
624			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
625			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
640			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
641			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
642			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
643			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
644			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
645			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
646			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
748			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
749			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
750			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
751			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
752			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
753			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
754			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
755			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
759			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1558			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1559			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1560			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1561			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1562			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1563			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1564			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1565			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1566			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1567			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1568			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1569			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1570			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1571			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1572			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1573			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1574			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1575			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1576			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1577			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1578			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
760			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
761			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
762			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
763			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
764			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
765			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
766			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
767			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
768			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
769			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
770			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
771			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
772			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
773			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
774			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
775			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
776			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
777			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
778			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
779			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
780			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
781			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
782			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
841			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
842			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
843			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
844			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
845			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
846			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
819			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
820			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
821			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
822			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
823			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
824			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
825			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
826			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
827			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
828			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
829			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
830			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
831			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
832			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
833			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
834			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1579			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1580			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1581			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1582			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1583			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1584			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1585			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1586			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1587			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1588			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1589			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1590			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1591			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1592			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1593			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
1594			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	1	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
835			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
836			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
837			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
838			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
839			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
840			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
859			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
860			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
861			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
862			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
863			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
864			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
756			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
757			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
758			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	0	0	0	0	0	0	0	\N	0	\N	\N	0	0	0	\N	\N
\.


--
-- Name: alarms_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('alarms_id_seq', 1, true);


--
-- Data for Name: enum_contexts; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY enum_contexts (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, type_partition, type_code, context_seq_number, metric_specification_update_period_seconds, metric_specification_update_period_nanoseconds, metric_specification_category, metric_specification_access, metric_specification_relevance, max_delay_time_seconds, max_delay_time_nanoseconds, vmo_label_string, vmo_source_list_vmo_type, vmo_source_list_glb_handle_context_id, vmo_source_list_glb_handle_handle, metric_source_list, unit_code, unit_label_string, msmt_site_list, body_site_list, metric_status, measure_period_value, measure_period_unit_code, averaging_period_value, averaging_period_unit_code, start_time_seconds, start_time_nanoseconds, stop_time_seconds, stop_time_nanoseconds, metric_calibration_cal_type, metric_calibration_cal_state, metric_calibration_cal_time_seconds, metric_calibration_cal_time_nanoseconds, color, measurement_status, metric_id, metric_info_label_string, substance_nomenclature_id, substance_nomenclature_code, substance_label_string, enum_measure_range, enum_measure_range_bits, enum_measure_range_labels_value, enum_measure_range_labels_label, created_at, updated_at) FROM stdin;
91			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
92			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
93			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
94			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
95			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
96			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
97			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
98			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
99			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
100			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
101			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
102			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
35			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
36			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
37			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
38			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
39			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
1			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
2			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
3			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
4			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
5			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
6			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
57			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
7			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
8			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
9			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
12			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
10			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
11			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
13			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
14			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
68			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
15			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
16			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
17			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
18			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
19			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
20			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
21			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
22			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
23			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
24			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
25			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
26			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
27			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
28			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
29			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
30			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
31			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
32			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
33			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
69			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
70			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
71			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
72			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
73			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
74			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
75			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
76			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
77			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
78			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
79			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
80			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
81			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
82			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
83			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
84			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
85			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
86			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
87			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
88			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
89			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
90			0	0	0	0	0	0	0	0	0	5	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
34			0	0	0	0	0	0	0	0	0	1	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
40			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
41			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
42			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
43			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
44			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
45			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
46			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
47			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
48			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
49			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
50			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
51			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
52			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
53			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
54			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
55			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
56			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
58			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
59			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
60			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
61			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
62			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
63			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
64			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
65			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
66			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
67			0	0	0	0	0	0	0	0	0	3	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N
\.


--
-- Name: enum_contexts_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('enum_contexts_id_seq', 1, true);


--
-- Data for Name: mds; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY mds (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, system_type_partition, system_type_code, system_model_manufacturer, system_model_model_number, nomenclature_version_nom_major_version, nomenclature_version_nom_minor_version, system_capability, system_specification_component_capab_id, system_specification_component_spec, production_specification_spec_type, production_specification_component_id, production_specification_prod_spec, mds_status, operating_mode, date_and_time_seconds, date_and_time_nanoseconds, relative_time_seconds, relative_time_nanoseconds, power_status, battery_level, remaining_battery_minutes, altitude_meters, line_frequency, created_at, updated_at) FROM stdin;
1			0	0	0	0	0	0			0	0	0	\N	\N	\N	\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N
\.


--
-- Name: mds_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('mds_id_seq', 1, true);


--
-- Data for Name: mp70db_version; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY mp70db_version (id, version) FROM stdin;
\.


--
-- Name: mp70db_version_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('mp70db_version_id_seq', 18, true);


--
-- Data for Name: numeric_contexts; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY numeric_contexts (id, instance_name, ice_id, context_id, handle, parent_handle, type_partition, type_code, metric_specification_update_period_seconds, metric_specification_update_period_nanoseconds, metric_specification_access, metric_specification_relevance, max_delay_time_seconds, max_delay_time_nanoseconds, vmo_label_string, vmo_source_list_vmo_type, vmo_source_list_glb_handle_context_id, vmo_source_list_glb_handle_handle, metric_source_list, unit_code, unit_label_string, msmt_site_list, body_site_list, metric_status, measure_period_value, measure_period_unit_code, averaging_period_value, averaging_period_unit_code, start_time_seconds, start_time_nanoseconds, stop_time_seconds, stop_time_nanoseconds, metric_calibration_cal_type, metric_calibration_cal_state, metric_calibration_cal_time_seconds, metric_calibration_cal_time_nanoseconds, color, measurement_status, metric_id, metric_info_label_string, substance_nomenclature_id, substance_nomenclature_code, substance_label_string, nu_measure_range_lower_value, nu_measure_range_upper_value, nu_physiological_range_lower_value, nu_physiological_range_upper_value, display_resolution_pre_point, display_resolution_post_point, accuracy, created_at, updated_at, source_timestamp_seconds, source_timestamp_nanoseconds, context_seq_number, metric_specification_category) FROM stdin;
1581		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1582		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1583		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1584		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1585		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1586		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1587		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1588		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1589		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1590		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1591		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1592		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1593		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1594		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1595		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1596		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1597		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1598		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1599		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1600		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1601		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1602		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1603		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1604		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1605		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1606		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1607		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1608		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1609		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1610		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1611		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1612		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1613		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1614		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1615		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1616		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1617		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1618		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1619		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1620		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1621		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1622		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1623		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1624		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1625		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1626		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1627		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1628		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1629		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1630		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1631		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1632		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1633		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1634		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1635		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1636		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1637		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1638		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1639		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1640		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1641		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1642		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1643		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1644		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1645		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1646		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
845		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
846		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
847		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
848		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
849		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
850		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
851		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
852		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
853		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
854		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
855		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
856		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
857		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
858		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
859		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
860		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
861		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
862		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
863		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
864		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
865		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
866		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
867		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
868		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
869		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
870		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
871		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
872		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
873		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
924		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
925		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
926		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
927		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
928		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
929		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
930		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
931		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
932		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
933		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
934		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
935		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
936		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
937		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
938		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
939		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
940		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
941		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
877		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
878		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
879		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
880		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
881		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
882		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
883		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
884		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
885		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
886		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
887		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
888		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
889		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
890		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
891		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
892		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
893		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
894		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
895		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
896		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
897		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
898		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
899		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
900		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
901		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
902		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
903		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
904		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
905		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
906		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
907		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
908		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
909		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1686		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1687		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1688		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1689		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1690		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1691		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1692		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1693		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1694		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1695		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1696		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1697		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1698		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1699		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1700		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1701		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1702		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1703		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1704		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1705		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1706		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1707		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1708		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1709		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1710		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1711		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1712		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1734		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1750		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1751		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1752		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1753		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1754		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1755		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1756		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1757		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1758		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1759		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1760		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1761		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1762		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1763		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1764		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1765		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1766		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1767		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1768		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1769		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1770		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1771		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1772		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1773		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1774		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1775		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1776		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1777		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1778		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1779		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1780		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1781		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1782		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1783		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1784		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1795		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1796		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1797		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1798		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1799		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1800		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1801		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1817		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1818		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1819		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1820		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1821		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1822		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1823		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1824		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1825		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1826		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1827		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1828		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1829		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1830		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1831		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1832		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1833		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1834		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1835		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1836		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1837		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1838		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1839		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1840		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1841		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1842		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1880		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1881		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1882		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1883		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1884		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1885		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1886		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1887		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1888		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1889		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1890		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1891		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1892		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1893		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1894		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1895		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1896		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1897		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1898		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1899		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1900		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1901		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1902		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1903		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1904		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1905		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1906		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1907		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1908		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1909		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1910		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1967		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1968		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1969		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1970		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1971		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1985		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1986		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1987		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1988		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1989		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1990		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1991		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1992		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1993		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1994		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1995		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1996		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1997		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2039		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2040		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2041		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2042		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2043		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2044		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2045		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2046		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2047		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2048		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2049		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2050		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2051		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2068		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2069		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2070		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2071		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2072		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2073		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2074		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2075		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2076		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2077		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2078		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2079		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2080		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2081		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2082		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2083		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2084		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2085		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2086		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2087		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2088		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2089		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2090		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2091		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2092		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2093		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2094		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2095		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2096		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2097		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2098		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2099		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2126		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2127		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2128		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2129		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2130		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2131		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2132		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2133		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2134		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2135		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2136		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2137		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2138		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2139		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2140		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2141		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2142		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2329		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2330		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2331		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2332		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2333		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2334		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2335		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2336		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2337		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2338		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2339		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2340		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2341		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2342		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2343		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2344		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2345		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2346		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2347		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2348		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2360		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2361		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2362		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2363		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2364		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2365		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2366		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2367		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2368		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2369		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2370		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2371		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2372		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2373		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2374		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2375		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2376		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2377		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2378		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2379		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2380		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2381		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2382		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2383		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2384		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2385		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1064		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1065		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1066		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1067		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1068		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1069		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1070		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1071		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1072		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1073		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1074		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1075		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1076		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1077		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1078		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2386		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2387		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2388		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2389		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2390		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2391		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2392		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1177		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1178		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1179		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1180		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1181		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1182		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1183		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1184		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1185		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1186		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1187		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1188		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1189		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1190		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2406		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2407		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2408		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2409		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2410		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2411		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2412		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2413		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2414		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2415		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2416		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2417		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2418		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2419		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2420		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2421		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2422		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2423		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2463		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
101		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
102		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
103		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
104		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
105		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
106		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
107		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
108		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
109		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
110		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
111		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
112		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
113		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
114		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
115		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
116		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
117		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
118		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
119		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1256		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1257		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1258		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1259		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1260		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1261		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1262		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1263		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1264		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1265		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
129		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
130		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
131		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
132		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
133		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
134		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
135		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
136		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
137		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
138		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
139		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
140		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
141		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
142		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
143		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
144		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
145		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
146		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
147		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
148		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
149		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
150		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
151		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
152		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
153		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
154		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
155		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
156		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
157		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
158		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
159		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
160		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
161		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
162		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
163		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
164		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
165		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
166		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
167		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
168		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
169		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
170		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
171		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
172		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
173		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
174		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
175		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
176		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
177		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
178		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
179		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
180		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
181		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
182		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
183		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
184		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
185		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
186		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
187		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
188		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
189		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
190		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
191		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
192		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
193		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
194		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
195		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1341		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1342		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1343		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
231		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
232		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
233		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
234		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
235		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
236		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
237		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
238		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
239		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
240		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
241		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
242		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
243		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
244		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
245		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
246		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
247		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
248		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
249		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
250		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
251		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
252		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
253		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
254		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
255		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
256		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
257		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
258		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
259		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
260		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
261		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
262		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
263		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
264		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
265		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
266		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
267		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
268		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
269		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
270		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
271		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
272		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
273		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
274		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
275		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
276		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
277		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
278		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
279		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
280		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
281		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
282		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
283		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
284		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
285		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
286		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
287		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
288		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
289		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
290		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
291		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
292		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
293		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
294		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
295		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
296		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
301		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
302		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
332		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
333		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
334		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
335		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
336		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
337		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
338		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
339		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
340		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
341		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
342		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
343		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
344		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
345		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
346		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
347		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
348		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
349		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
350		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
351		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
352		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
353		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
354		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
355		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
356		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
357		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
358		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
359		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
360		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
361		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
362		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
363		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
364		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
365		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
366		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
367		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
368		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
369		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
370		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
371		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
372		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
373		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
374		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
375		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
376		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
377		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
378		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
379		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
380		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
381		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
382		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
383		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
384		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
385		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
386		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
387		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
388		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
389		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
390		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
391		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
392		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
393		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
394		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
395		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1463		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1464		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1465		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1466		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1467		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1468		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1469		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1470		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1471		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1472		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1473		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1474		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1475		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1476		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1477		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1478		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1479		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1480		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1481		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1482		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1483		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1484		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1485		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1486		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1487		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1488		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1489		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
396		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
397		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
398		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
399		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
400		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
401		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
402		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
403		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
404		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
405		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
406		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
407		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
408		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
409		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
410		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
411		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
412		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
413		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
414		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
415		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
416		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
417		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
418		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
419		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
911		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
912		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
913		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
914		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
915		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
916		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
917		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
918		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
919		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
920		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
921		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
922		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
923		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
950		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
951		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
952		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
953		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
954		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
955		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
956		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
957		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
958		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
959		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
960		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
961		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
962		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
963		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
964		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
965		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
966		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
967		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
968		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
969		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
970		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
971		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
972		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
973		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
974		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
975		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
976		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
977		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
978		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
979		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
980		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
981		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
982		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
983		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
984		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
985		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
986		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
987		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
988		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
989		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
990		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
991		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
992		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
993		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1524		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1525		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1526		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1527		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1528		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1529		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1530		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1531		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1532		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1533		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1534		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1535		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1536		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1537		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1538		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1539		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1540		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1541		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1542		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1543		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1544		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1545		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1546		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1547		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1548		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
994		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
995		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
996		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
997		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
998		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
999		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1000		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1001		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1002		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1003		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1004		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1005		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1006		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1007		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1008		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1009		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1010		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1011		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1012		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1013		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1014		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1015		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1016		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1017		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1018		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1019		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1020		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1021		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1022		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1023		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1024		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1025		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1026		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1027		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1028		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
443		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
444		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
445		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
516		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
517		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
518		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
519		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
520		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
521		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
522		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
523		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
524		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
525		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
526		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
527		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
528		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
529		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
530		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
531		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
532		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
533		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
534		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
535		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
536		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
537		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
538		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
539		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
540		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
541		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
542		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
543		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
544		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
545		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
546		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
547		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
548		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
549		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
550		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
551		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
552		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
553		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
554		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
555		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
556		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
557		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
558		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
559		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
560		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
561		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
562		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
563		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
564		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
565		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
566		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
567		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
568		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
569		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
570		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
571		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
572		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
573		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
574		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
575		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
576		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
577		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
578		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
579		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
580		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
581		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
582		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
583		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
584		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
585		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
586		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
587		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
588		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
589		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
590		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
591		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
592		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
593		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
594		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
595		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
596		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
597		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1132		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1133		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1134		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1135		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1136		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1137		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1138		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1139		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1140		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1141		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1142		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1143		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1144		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1145		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1146		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1147		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1148		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1149		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1150		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1151		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1152		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1153		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1154		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1155		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1156		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1212		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1213		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1214		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1215		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1216		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1217		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1218		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1219		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1220		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1221		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1222		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1223		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1224		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1225		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1226		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1227		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1228		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1229		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1230		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1231		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1232		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1233		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1234		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1235		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1236		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1237		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1238		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1239		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1240		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1241		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1242		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1243		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1244		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1245		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1246		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1247		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1248		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1249		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1250		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1251		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1252		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1253		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1254		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1255		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
910		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1666		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1667		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1668		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1669		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1670		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1671		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1672		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1673		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1674		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1675		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1676		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1677		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1678		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1679		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1680		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1681		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1682		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1683		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1684		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1685		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1735		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1736		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1737		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1738		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1739		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1740		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1741		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1742		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1743		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1744		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1745		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1746		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1747		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1748		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1749		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1915		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1916		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1917		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1918		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1919		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1920		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1921		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1922		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1923		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1924		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1925		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1926		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1927		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1928		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1929		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1930		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1931		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1932		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1933		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1934		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1935		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1936		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1937		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1938		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1939		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1940		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1941		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1942		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1943		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1944		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1945		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1946		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1947		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1948		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1949		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1950		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1951		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1952		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1953		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1954		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1955		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1956		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2151		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2152		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2153		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2154		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2155		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2156		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2157		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2158		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2159		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2160		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2161		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2162		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2163		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2164		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2165		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2166		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2167		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2168		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2169		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2170		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2171		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2172		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2173		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2174		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2175		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2176		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2177		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2178		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2179		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2180		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2181		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2182		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2183		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2184		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2185		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2186		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2187		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2188		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2189		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2190		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2191		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2192		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2193		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1157		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1158		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1159		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1160		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1161		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1162		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1163		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1164		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1165		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1166		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1167		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1168		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1169		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1170		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1171		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1172		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1173		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1174		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1175		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1176		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
598		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
599		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
600		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
601		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1647		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1648		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1649		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1650		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
826		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
827		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
828		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
829		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1288		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1289		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1290		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1291		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1292		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1293		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1294		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1295		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1296		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1297		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1298		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1299		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1300		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1301		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1302		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1303		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1304		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1305		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1306		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1307		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1308		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1309		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1310		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1311		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1312		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1313		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1314		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1315		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1316		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1317		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1318		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1319		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1320		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1321		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1322		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1323		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1361		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1362		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1363		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1364		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1365		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1366		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1367		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1368		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1369		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1370		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1371		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1372		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1373		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1374		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1375		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1376		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1377		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1378		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1379		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1380		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1381		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1382		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1383		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1384		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1385		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1386		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1387		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1388		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1389		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1390		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1391		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1392		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1393		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1394		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1395		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1396		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1397		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1398		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1428		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1429		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1430		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1431		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1432		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1433		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1434		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1435		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1436		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1437		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1438		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1439		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1440		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1441		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1442		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1443		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1444		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1445		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1446		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1447		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1448		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1449		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1450		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1451		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1452		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1453		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1454		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1455		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1456		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1457		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1458		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1459		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1460		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1461		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1462		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1399		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1400		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1843		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1844		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1845		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1846		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1866		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1867		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1868		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1869		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1870		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1871		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1872		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1873		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1874		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1875		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1876		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1490		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1491		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1492		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1493		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1494		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1495		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1496		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1497		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1498		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1499		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1500		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1501		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1502		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1503		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1504		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1505		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1506		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1507		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1508		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1509		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1510		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1511		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1512		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1513		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1514		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1515		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1516		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1517		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1518		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1519		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1520		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1521		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1522		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1523		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2052		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2053		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2054		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2055		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2056		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2057		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1549		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1550		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1551		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1552		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1553		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1554		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1555		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1556		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1557		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1558		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1559		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1560		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1561		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1562		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1563		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1564		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1565		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1566		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1567		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1568		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1569		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1570		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1571		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1572		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1573		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1574		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1575		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1576		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1577		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1578		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1579		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1580		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2100		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2101		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2102		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2103		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2104		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2105		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2118		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2119		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2120		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2121		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2122		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2123		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2124		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2125		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2349		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2350		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2351		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2352		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2353		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2354		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2355		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2356		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2357		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2358		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2359		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1266		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1267		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1268		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1269		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1270		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1271		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1272		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1273		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1274		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1275		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1276		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1277		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1278		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1279		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1280		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1281		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1282		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1283		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1284		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1285		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1286		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1287		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
120		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
121		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
122		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
123		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
124		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
125		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
126		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
127		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
128		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2058		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
297		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
298		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
299		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
300		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1401		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1402		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1403		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1404		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1405		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1406		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1407		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1408		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1409		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1410		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1411		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1412		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1413		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1414		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1415		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1416		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1417		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1418		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1419		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1420		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1421		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1422		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1423		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1424		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1425		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1426		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1427		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2059		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2060		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2061		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2062		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2063		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2064		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2065		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2066		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2067		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2106		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2107		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2108		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2109		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2110		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2111		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2112		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2113		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2114		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2115		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2116		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2117		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1191		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1192		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1193		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1194		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1195		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1196		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1197		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1198		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1199		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1200		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1201		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1202		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1203		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1204		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1205		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1206		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1207		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1208		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1209		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1210		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1211		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2393		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2394		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2395		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2396		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2397		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2398		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2399		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2400		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2401		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2402		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2403		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2404		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2405		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
196		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
197		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
198		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
199		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
200		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
201		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
202		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
203		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
204		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
205		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
206		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
207		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
208		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
209		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
210		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
211		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
212		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
213		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
214		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
215		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
216		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1329		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1330		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1331		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1332		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1333		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1334		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1335		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1336		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1337		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1338		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1339		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1340		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1877		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1878		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1879		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1972		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1973		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1974		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1975		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1976		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1977		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1978		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1979		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1980		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1981		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1982		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1983		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1984		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2143		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2144		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2145		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2146		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2147		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2271		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2272		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2273		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2274		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2275		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2276		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2277		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2278		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2279		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2280		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2281		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2282		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2283		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2284		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2285		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2286		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2287		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
303		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
304		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
305		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
306		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
307		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
308		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
309		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
310		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
311		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
312		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
313		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
314		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
315		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
316		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
317		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
318		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
319		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
320		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
321		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
322		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
323		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
324		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
325		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
326		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
327		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
328		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
329		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
330		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
331		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2288		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2289		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2290		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2291		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2292		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2293		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2294		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2324		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2325		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2326		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2327		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2328		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1847		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1848		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2464		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2465		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
36		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
37		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
38		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
39		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
40		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
41		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
42		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
43		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
44		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
45		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
46		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
47		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
48		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
49		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
50		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
51		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
52		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
53		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
54		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
55		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
56		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
57		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
58		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
59		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
60		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
61		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
62		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
63		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
64		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
65		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
66		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
67		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
68		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
69		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1849		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1850		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1851		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1852		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1853		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1854		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1855		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1856		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1857		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1858		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1859		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1860		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1861		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1862		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1863		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1864		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1865		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1911		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1912		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1913		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1914		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1957		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1958		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1959		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1960		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1961		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1962		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1963		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1964		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1965		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1966		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2148		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2149		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2150		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2194		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2195		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2196		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2238		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2239		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2240		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2241		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2242		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2243		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2244		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2245		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2246		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2247		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2248		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1344		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1345		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1346		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1347		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1348		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1349		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1350		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1351		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1352		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1353		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1354		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1355		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1356		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1357		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1358		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1359		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1360		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
217		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
218		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
219		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
220		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
221		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
222		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
223		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
224		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
225		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
226		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
227		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
228		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
229		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
230		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2249		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2250		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2251		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2252		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2253		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2254		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2255		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2256		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2257		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2258		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2259		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2260		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2261		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2262		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2263		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2264		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2265		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2266		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2267		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2268		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2269		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2270		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2424		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2425		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2426		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2427		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2428		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2429		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2430		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2431		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2432		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2433		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2434		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2435		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2436		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2437		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2438		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2439		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2440		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2441		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2442		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1716		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2004		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2005		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2006		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1717		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1718		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1719		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1720		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1721		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1722		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1723		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1724		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1725		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1998		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1999		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2000		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2001		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2002		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2003		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2007		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2008		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2009		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2010		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2011		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2012		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2013		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2014		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2015		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2016		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2017		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2018		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2019		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2020		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2021		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2022		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2023		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2024		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2025		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2309		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2310		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2311		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2312		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1651		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1652		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1653		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1654		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1655		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1656		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1657		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1658		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1029		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1030		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1031		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1032		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1033		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1034		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1035		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
70		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
71		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
72		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
73		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
74		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
75		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
76		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
77		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
78		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
79		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
80		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
81		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
82		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
83		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
84		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
85		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
86		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
87		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
88		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
89		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
90		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
91		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
92		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
93		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
94		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
95		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
96		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
97		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
98		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
99		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
100		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1036		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1037		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1038		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1039		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1040		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1041		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1042		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1043		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1044		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
834		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
835		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2443		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2444		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2445		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2446		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2447		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2448		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2449		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2450		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2451		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2452		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2453		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2454		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2455		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2456		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2457		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2458		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2459		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2460		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2461		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2462		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1324		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1325		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1326		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1327		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1328		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
830		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
831		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
832		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1713		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1714		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1715		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1726		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1727		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1813		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1814		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1815		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1816		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
836		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
837		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
838		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
839		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
840		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
841		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
842		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
843		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
844		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
446		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1728		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1729		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1730		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1731		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1732		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1733		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1802		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1803		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1804		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1805		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1806		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1807		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1808		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1809		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1810		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1811		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1812		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
447		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
448		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
449		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
450		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
451		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
452		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
453		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
454		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
455		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
456		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
457		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
458		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
459		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
874		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
875		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
876		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1785		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1786		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2466		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2467		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
3		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
4		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
5		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
6		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
7		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
8		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
9		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
10		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
11		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
12		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
13		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
14		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
15		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
16		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
17		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
18		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
19		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
20		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
21		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
22		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
23		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
24		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
25		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
26		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
27		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
28		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
29		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
30		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
31		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
32		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
33		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
34		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
35		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1787		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1788		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1789		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1790		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1791		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1792		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1793		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1794		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
465		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2026		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2027		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2028		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2029		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2030		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2031		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2032		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2033		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2034		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
466		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
467		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
468		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
469		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
470		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
471		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
486		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
487		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
488		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
489		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
490		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
491		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
492		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
493		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
494		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
495		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
496		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
497		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
498		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
499		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
500		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1079		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1080		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1081		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1082		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1083		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1084		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1085		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1086		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1087		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1088		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1089		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1090		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1091		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1092		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1093		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1094		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1095		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1096		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1097		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1098		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1099		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1100		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1101		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1102		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1103		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1104		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1105		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1106		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2199		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2200		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2201		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
642		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
643		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
644		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
645		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2035		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2036		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2037		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2038		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
833		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2295		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2296		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2297		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2298		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2299		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2300		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2301		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2302		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2303		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2304		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2305		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2306		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2307		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2308		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
472		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
473		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
474		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
475		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
476		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
477		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
478		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
479		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
480		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
481		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
482		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
483		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
484		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
485		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
646		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
647		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
648		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
649		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
650		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
651		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
652		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
674		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
675		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
676		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
677		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
678		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
679		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
680		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
681		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
682		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
683		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
684		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
685		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
686		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2321		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2322		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2323		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
698		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
699		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
706		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
707		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
708		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
709		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1107		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1108		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1109		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1110		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1111		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1112		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1113		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1114		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1115		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1116		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1117		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1118		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1119		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1120		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1121		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1122		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1123		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1124		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
602		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
603		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
604		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
605		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
606		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
607		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
608		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
609		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
610		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
611		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
612		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
613		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
614		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
615		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
616		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
617		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2197		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2198		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2212		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2213		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2214		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2215		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2216		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2217		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2218		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2219		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2220		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2221		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2222		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2223		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2224		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2225		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2226		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2227		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2228		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2229		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2230		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2231		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2232		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2233		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2234		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2235		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2236		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2237		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
618		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
710		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
745		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
746		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
747		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
748		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2202		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
687		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
688		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
689		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
690		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
691		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
692		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
693		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
694		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
695		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
696		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
697		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1045		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1046		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
2203		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2204		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2205		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2206		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2207		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2208		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2209		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2210		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2211		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
619		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
620		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
621		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
622		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
623		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
624		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
625		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
626		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
627		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
628		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
629		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
630		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
631		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
632		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
633		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
634		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
635		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
636		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
637		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
638		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
639		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
640		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
641		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
789		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
790		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
791		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
792		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
793		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
794		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
795		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
796		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
797		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
798		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
799		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1047		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1048		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1049		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1050		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1051		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1052		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1053		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1054		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1055		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1056		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1057		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1058		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1059		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1060		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1061		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1062		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1063		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1659		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1660		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1661		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1662		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1663		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1664		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
1665		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2313		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2314		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2315		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2316		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2317		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2318		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2319		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2320		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
700		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
701		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
702		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
703		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
704		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
705		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
800		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
801		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
802		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
803		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
804		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
430		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
431		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
432		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
433		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
434		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
435		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
436		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
437		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
438		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
439		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
440		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
441		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
442		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
711		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
712		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
713		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
714		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
715		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
716		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
717		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
718		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
719		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
720		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
721		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
722		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
723		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
724		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
725		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
726		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
727		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
728		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
729		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
730		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
731		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
732		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
733		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
734		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
942		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
943		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
944		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
945		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
946		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
947		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
948		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
949		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
460		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
461		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
462		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
463		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
464		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
501		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
502		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
503		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
504		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
505		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
506		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
507		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
508		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
509		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
510		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
511		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
512		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
513		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
514		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
515		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1125		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
805		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
806		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
807		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
808		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
809		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
810		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
811		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
812		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
813		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
814		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
815		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
816		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
817		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
818		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
819		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
820		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
821		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
822		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
823		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
824		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
825		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
2468		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2469		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2470		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2471		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2472		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2473		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2474		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
2475		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5
420		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
421		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
422		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
423		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
424		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
425		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
426		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
427		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
428		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
429		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
653		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
654		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
655		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
656		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
657		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
658		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
659		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
660		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
661		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
662		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
663		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
664		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
665		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
666		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
667		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
668		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
669		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
749		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
750		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
751		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
752		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
753		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
754		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
755		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
756		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
757		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
758		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
759		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
760		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
761		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
762		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
763		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
764		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
765		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
766		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
767		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
768		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
769		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
770		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
771		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
772		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
773		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
774		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
775		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
776		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
777		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
778		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
779		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
780		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
781		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
782		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
783		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
784		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
785		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
786		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
787		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
788		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
670		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
671		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
672		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
673		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
735		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
736		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
737		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
738		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
739		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
740		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
741		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
742		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
743		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
744		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1
1126		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1127		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1128		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1129		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1130		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
1131		\N	0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3
\.


--
-- Name: numeric_contexts_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('numeric_contexts_id_seq', 1650, true);


--
-- Data for Name: pat_demo_reqs; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY pat_demo_reqs (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, sex, gender, race_race_type, race_provenance, patient_type, chronological_age_value, chronological_age_m_unit, patient_height_value, patient_height_m_unit, patient_weight_value, patient_weight_m_unit, neonatal_gestational_age_value, neonatal_gestational_age_m_unit, neonatal_patient_birth_length_value, neonatal_patient_birth_length_m_unit, neonatal_patient_birth_weight_value, neonatal_patient_birth_weight_m_unit, neonatal_patient_head_circumference_value, neonatal_patient_head_circumference_m_unit, neonatal_mother_patient_id_given_name, neonatal_mother_patient_id_family_name, neonatal_mother_patient_id_middle_name, neonatal_mother_patient_id_date_of_birth_century, neonatal_mother_patient_id_date_of_birth_year, neonatal_mother_patient_id_date_of_birth_month, neonatal_mother_patient_id_date_of_birth_day, neonatal_mother_patient_id_patient_id, neonatal_mother_patient_id_patient_id_provenance, neonatal_mother_patient_id_verified, neonatal_mother_patient_id_pat_admit_state, neonatal_mother_patient_id_pat_episode_id, neonatal_mother_patient_id_episode_start_seconds, neonatal_mother_patient_id_episode_start_nanoseconds, neonatal_mother_name, created_at, updated_at) FROM stdin;
1	demo	test ice id	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	2016-01-05 22:03:49.235188	2016-01-05 22:03:51.564763
\.


--
-- Name: pat_demos_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('pat_demos_id_seq', 1, true);


--
-- Data for Name: pat_ident_reqs; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY pat_ident_reqs (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, given_name, family_name, middle_name, date_of_birth_century, date_of_birth_year, date_of_birth_month, date_of_birth_day, patient_id, patient_id_provenance, verified, pat_admit_state, pat_episode_id, episode_start_seconds, episode_start_nanoseconds, created_at, updated_at) FROM stdin;
1	id	test ice id	0	0	0	0				\N	\N	\N	\N		\N	f	0	0	0	0	2016-01-05 22:03:44.609316	2016-01-05 22:03:46.959673
\.


--
-- Name: pat_idents_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('pat_idents_id_seq', 1, true);


--
-- Data for Name: sample_array_contexts; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY sample_array_contexts (id, instance_name, context_id, handle, parent_handle, type_partition, type_code, metric_specification_update_period_seconds, metric_specification_update_period_nanoseconds, metric_specification_access, metric_specification_relevance, max_delay_time_seconds, max_delay_time_nanoseconds, vmo_label_string, vmo_source_list_vmo_type, vmo_source_list_glb_handle_context_id, vmo_source_list_glb_handle_handle, metric_source_list, unit_code, unit_label_string, msmt_site_list, body_site_list, metric_status, measure_period_value, measure_period_unit_code, averaging_period_value, averaging_period_unit_code, start_time_seconds, start_time_nanoseconds, stop_time_seconds, stop_time_nanoseconds, metric_calibration_cal_type, metric_calibration_cal_state, metric_calibration_cal_time_seconds, metric_calibration_cal_time_nanoseconds, color, measurement_status, metric_id, metric_info_label_string, substance_nomenclature_id, substance_nomenclature_code, substance_label_string, sa_specification_array_size, sa_specification_sample_type_sample_size, sa_specification_sample_type_significant_bits, sa_specification_sample_type_signed_samples, sa_specification_flags, compression, sa_marker_list_marker_id, sa_marker_list_marker_val, scale_and_range_specification_lower_absolute_value, scale_and_range_specification_upper_absolute_value, scale_and_range_specification_lower_scaled_value, scale_and_range_specification_upper_scaled_value, sa_physiological_range_lower_scaled_value, sa_physiological_range_upper_scaled_value, visual_grid_absolute_value, visual_grid_scaled_value, visual_grid_level, sa_calibration_data_lower_absolute_value, sa_calibration_data_upper_absolute_value, sa_calibration_data_lower_scaled_value, sa_calibration_data_upper_scaled_value, sa_calibration_data_increment, sa_calibration_data_cal_type, filter_specification_filter_type, filter_specification_filter_frequency, filter_specification_filter_order, filter_label_string, sa_signal_frequencey_low_edge_freq, sa_signal_frequencey_high_edge_freq, sa_measure_resolution, sample_period_seconds, sample_period_nanoseconds, sweep_speed_value, sweep_speed_unit_code, average_reporting_delay_seconds, average_reporting_delay_nanoseconds, sample_time_sync_seconds, sample_time_sync_nanoseconds, created_at, updated_at, ice_id, source_timestamp_nanoseconds, source_timestamp_seconds, context_seq_number, metric_specification_category, sa_signal_frequency_low_edge_freq, sa_signal_frequency_high_edge_freq) FROM stdin;
446		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
447		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
448		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
449		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
90		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
91		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
101		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
102		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
103		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
104		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
105		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
106		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
107		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
108		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
196		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
197		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
198		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
199		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
200		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
201		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
202		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
203		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
204		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
205		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
206		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
207		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
208		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
209		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
210		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
211		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
212		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
213		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
214		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
215		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
216		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
217		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
279		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
280		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
281		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
282		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
283		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
224		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
225		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
569		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
570		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
229		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
230		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
293		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
294		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
295		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
296		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
297		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
298		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
299		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
300		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
301		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
302		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
303		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
304		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
305		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
306		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
307		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
308		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
309		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
623		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
624		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
625		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
626		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
627		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
129		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
130		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
131		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
132		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
133		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
134		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
165		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
139		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
96		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
97		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
98		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
99		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
100		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
284		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
285		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
286		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
287		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
288		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
289		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
166		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
167		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
168		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
321		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
322		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
323		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
324		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
325		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
326		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
327		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
328		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
329		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
330		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
380		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
381		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
382		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
474		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
475		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
476		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
146		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
147		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
148		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
149		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
655		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
656		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
657		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
658		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
659		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
660		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
661		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
662		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
663		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
664		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
665		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
666		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
667		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
668		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
579		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
704		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
705		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
706		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
707		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
708		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
709		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
710		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
711		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
712		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
713		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
714		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
715		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
768		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
717		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
718		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
719		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
720		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
721		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
722		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
723		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
724		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
725		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
726		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
727		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
728		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
729		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
730		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
731		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
732		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
737		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
738		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
769		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
770		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
771		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
772		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
773		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
774		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
531		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
560		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
561		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
456		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
457		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
458		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
459		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
460		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
461		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
462		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
633		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
634		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
649		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
535		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
536		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
537		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
538		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
539		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
540		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
541		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
542		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
543		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
544		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
545		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
546		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
547		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
463		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
464		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
465		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
466		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
467		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
468		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
469		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
470		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
471		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
265		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
266		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
267		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
268		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
269		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
270		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
80		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
81		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
82		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
83		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
84		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
85		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
4		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
5		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
6		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
7		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
8		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
9		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
10		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
11		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
271		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
272		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
22		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
23		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
506		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
507		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
508		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
509		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
510		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
511		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
512		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
513		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
514		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
451		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
24		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
25		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
671		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
374		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
189		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
190		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
157		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
672		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
673		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
674		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
675		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
676		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
677		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
678		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
70		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
71		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
72		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
73		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
74		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
75		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
684		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
739		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
740		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
741		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
742		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
743		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
744		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
745		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
746		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
747		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
748		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
749		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
750		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
751		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
752		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
753		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
685		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
686		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
687		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
77		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
78		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
79		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
454		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
140		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
186		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
187		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
550		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
551		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
552		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
553		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
554		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
26		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
27		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
28		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
29		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
30		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
31		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
42		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
43		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
44		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
45		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
555		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
556		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
557		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
558		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
559		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
562		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
563		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
46		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
564		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
188		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
688		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
689		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
690		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
691		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
692		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
693		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
694		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
754		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
755		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
756		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
757		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
758		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
759		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
48		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
49		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
50		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
51		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
52		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
53		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
54		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
55		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
56		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
57		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
86		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
87		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
47		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
760		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
761		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
762		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
601		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
603		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
604		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
450		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
651		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
652		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
653		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
654		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
316		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
12		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
418		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
585		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
3		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
218		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
315		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
317		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
437		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
438		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
439		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
277		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
278		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
291		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
292		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
318		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
319		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
320		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
219		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
220		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
221		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
222		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
223		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
311		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
312		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
331		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
332		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
333		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
453		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
388		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
389		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
359		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
375		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
376		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
58		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
59		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
60		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
61		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
62		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
76		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
695		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
696		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
697		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
698		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
699		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
89		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
34		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
35		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
36		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
37		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
232		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
233		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
234		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
235		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
618		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
619		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
38		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
39		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
40		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
41		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
620		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
109		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
110		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
111		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
112		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
113		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
153		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
154		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
155		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
156		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
150		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
169		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
631		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
632		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
170		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
171		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
172		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
733		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
734		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
735		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
434		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
435		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
436		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
173		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
174		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
175		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
383		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
384		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
385		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
386		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
387		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
571		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
572		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
573		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
574		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
575		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
576		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
577		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
472		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
176		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
177		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
611		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
612		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
613		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
360		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
361		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
362		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
363		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
364		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
114		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
473		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
115		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
116		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
117		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
669		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
158		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
159		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
160		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
161		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
679		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
680		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
681		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
682		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
683		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
63		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
64		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
65		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
66		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
67		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
68		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
69		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
141		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
142		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
523		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
524		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
525		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
586		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
587		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
588		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
589		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
590		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
591		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
592		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
143		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
144		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
775		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
776		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
777		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
778		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
779		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
780		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
781		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
782		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
783		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
784		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
785		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
635		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
636		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
637		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
638		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
639		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
640		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
641		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
642		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
643		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
644		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
645		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
646		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
647		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
786		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
787		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
788		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
529		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
530		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
516		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
517		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
606		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
607		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
610		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
347		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
14		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
15		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
16		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
648		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
17		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
18		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
399		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
440		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
441		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
442		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
443		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
444		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
445		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
19		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
20		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
1		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
431		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
420		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
421		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
422		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
423		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
424		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
425		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
426		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
427		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
428		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
429		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
430		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
390		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
391		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
392		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
393		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
394		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
395		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
396		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
397		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
245		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
184		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
185		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
183		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
145		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
736		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
92		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
93		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
94		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
95		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
226		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
227		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
228		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
565		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
566		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
567		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
568		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
236		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
237		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
238		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
239		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
240		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
241		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
242		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
243		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
244		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
151		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
152		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
614		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
615		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
616		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
617		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
164		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
670		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
477		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
478		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
479		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
480		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
482		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
483		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
484		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
485		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
486		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
487		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
488		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
489		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
578		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
455		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
310		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
313		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
314		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
231		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
621		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
622		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
628		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
629		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
630		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
178		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
179		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
180		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
181		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
182		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
766		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
136		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
137		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
138		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
767		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
162		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
163		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
334		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
335		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
336		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
337		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
338		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
339		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
340		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
341		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
342		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
343		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
344		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
345		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
346		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
379		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
118		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
119		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
120		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
121		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
122		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
123		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
124		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
125		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
126		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
127		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
128		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
273		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
276		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
365		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
366		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
367		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
368		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
369		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
370		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
371		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
372		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
548		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
549		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
650		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
191		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
192		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
193		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
194		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
195		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
274		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
275		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
763		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
764		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
765		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
518		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
519		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
520		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
521		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
522		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
526		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
527		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
528		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
602		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
593		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
594		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
595		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
596		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
597		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
598		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
599		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
600		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
532		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
88		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
348		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
533		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
534		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
581		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
582		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
583		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
349		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
350		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
351		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
352		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
353		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
354		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
355		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
356		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
357		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
358		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
584		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
432		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
433		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
400		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
401		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
402		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
403		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
404		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
405		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
406		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
407		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
408		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
409		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
410		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
411		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
412		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
413		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
414		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
415		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
416		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
417		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
2		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
246		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
247		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
248		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
249		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
250		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
251		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
252		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
253		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
254		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
255		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
256		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
257		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
258		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
259		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
260		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
261		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
262		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
263		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
264		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
789		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
790		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
791		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
792		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
580		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
481		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
135		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
290		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
452		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
373		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
605		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
377		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
378		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
490		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
491		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
492		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
493		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
494		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
495		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
496		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
497		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
498		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
499		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
500		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
501		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
502		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
503		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
504		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
505		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
21		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
515		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
608		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
609		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
700		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
701		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
702		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
703		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
716		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	5	\N	\N
32		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
33		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
13		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	1	\N	\N
419		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
398		0	0	0	0	0	0	0	0	0	\N	\N		\N	\N	\N	\N	0		\N	\N	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0		\N	\N		0	\N	\N	\N	0	\N	\N	\N	0	0	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N	\N		\N	\N	\N	0	0	\N	\N	\N	\N	\N	\N	\N	\N	\N	0	0	0	3	\N	\N
\.


--
-- Name: sample_array_contexts_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('sample_array_contexts_id_seq', 264, true);


--
-- Data for Name: schema_migrations; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY schema_migrations (version) FROM stdin;
20151002155657
20151002155703
20151002155722
20151123235506
20151124194525
20151222225959
20151223142519
20160105205347
20160105205417
20160105214356
20160105214357
20160107233044
\.


--
-- Data for Name: table_versions; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY table_versions (id, name, created_at, updated_at) FROM stdin;
1	109.400000000000006	2015-11-24 00:26:40.305185	2016-01-07 23:38:05.00657
\.


--
-- Name: table_versions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('table_versions_id_seq', 2, true);


--
-- Data for Name: vmds; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY vmds (id, instance_name, ice_id, handle, parent_handle, source_timestamp_seconds, source_timestamp_nanoseconds, type_partition, type_code, instance_number, measurement_principle, locale_language, locale_country, locale_charset, locale_str_spec_str_max_len, locale_str_spec_str_flags, vmo_label_string, vmd_status, "position", operating_hours, operation_cycles, vmd_model_manufacturer, vmd_model_model_number, production_specification_spec_type, production_specification_component_id, production_specification_prod_spec, created_at, updated_at) FROM stdin;
1	vmd		0	0	0	0	0	0	0	\N	0	0	0	0	0		0	0	\N	\N			\N	\N	\N	2015-11-24 20:05:14.294981	2015-11-24 20:05:16.446455
\.


--
-- Name: vmds_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('vmds_id_seq', 1, true);


--
-- Name: alarms_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY alarms
    ADD CONSTRAINT alarms_pkey PRIMARY KEY (id);


--
-- Name: enum_contexts_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY enum_contexts
    ADD CONSTRAINT enum_contexts_pkey PRIMARY KEY (id);


--
-- Name: mds_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY mds
    ADD CONSTRAINT mds_pkey PRIMARY KEY (id);


--
-- Name: numeric_contexts_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY numeric_contexts
    ADD CONSTRAINT numeric_contexts_pkey PRIMARY KEY (id);


--
-- Name: pat_demos_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY pat_demo_reqs
    ADD CONSTRAINT pat_demos_pkey PRIMARY KEY (id);


--
-- Name: pat_idents_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY pat_ident_reqs
    ADD CONSTRAINT pat_idents_pkey PRIMARY KEY (id);


--
-- Name: pk_mp70db_version; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY mp70db_version
    ADD CONSTRAINT pk_mp70db_version PRIMARY KEY (id);


--
-- Name: sample_array_contexts_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY sample_array_contexts
    ADD CONSTRAINT sample_array_contexts_pkey PRIMARY KEY (id);


--
-- Name: table_versions_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY table_versions
    ADD CONSTRAINT table_versions_pkey PRIMARY KEY (id);


--
-- Name: vmds_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY vmds
    ADD CONSTRAINT vmds_pkey PRIMARY KEY (id);


--
-- Name: unique_schema_migrations; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX unique_schema_migrations ON schema_migrations USING btree (version);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

