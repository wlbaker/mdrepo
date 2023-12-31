
/*
 * Copyright (C) 2010 Archie L. Cobbs. All rights reserved.
 *
 * $Id: AbstractComPortCommandSwitch.java 6 2010-11-20 23:37:06Z archie.cobbs $
 */

package org.dellroad.jvser;

/**
 * Adapter class for {@link ComPortCommandSwitch} implementations.
 *
 * @see ComPortCommandSwitch
 * @see ComPortCommand#visit
 */
public class AbstractComPortCommandSwitch implements ComPortCommandSwitch {

    /**
     * Visit method invoked by {@link SignatureCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseSignature(SignatureCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link BaudRateCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseBaudRate(BaudRateCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link DataSizeCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseDataSize(DataSizeCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link ParityCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseParity(ParityCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link StopSizeCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseStopSize(StopSizeCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link ControlCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseControl(ControlCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link NotifyLineStateCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseNotifyLineState(NotifyLineStateCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link NotifyModemStateCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseNotifyModemState(NotifyModemStateCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link FlowControlSuspendCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseFlowControlSuspend(FlowControlSuspendCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link FlowControlResumeCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseFlowControlResume(FlowControlResumeCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link LineStateMaskCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseLineStateMask(LineStateMaskCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link ModemStateMaskCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void caseModemStateMask(ModemStateMaskCommand command) {
        caseDefault(command);
    }

    /**
     * Visit method invoked by {@link PurgeDataCommand} instances.
     *
     * <p>
     * The implementation in {@link AbstractComPortCommandSwitch} delegates to {@link #caseDefault}.
     * </p>
     */
    @Override
	public void casePurgeData(PurgeDataCommand command) {
        caseDefault(command);
    }

    /**
     * Default handler.
     *
     * <p>
     * All other methods in {@link AbstractComPortCommandSwitch} delegate to this method;
     * the implementation in {@link AbstractComPortCommandSwitch} does nothing.
     * </p>
     */
    protected void caseDefault(ComPortCommand command) {
    }
}

