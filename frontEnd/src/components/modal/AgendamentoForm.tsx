import { useEffect, useState } from 'react'
import { api } from '../../services/api'

interface Props {
  onCancel: () => void
  onSave: (payload?: any) => void
}

export default function AgendamentoForm({ onCancel, onSave }: Props) {
  // dados carregados da api
  const [clients, setClients] = useState<Array<{ id: number; name: string }>>([])
  const [barbers, setBarbers] = useState<Array<{ id: number; name: string }>>([])
  const [services, setServices] = useState<Array<{ id: number; name: string }>>([])

  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)

  // campos do formulario
  const [clientId, setClientId] = useState<number | ''>('')
  const [barberId, setBarberId] = useState<number | ''>('')
  const [serviceId, setServiceId] = useState<number | ''>('')
  const [date, setDate] = useState('')
  const [time, setTime] = useState('')
  const [status, setStatus] = useState<'agendado' | 'concluido'>('agendado')

  // efeitos para carregar dados iniciais
  useEffect(() => {
    let mounted = true
    setLoading(true)
    Promise.all([api.getClients(), api.getBarbers(), api.getServices()])
      .then(([c, b, s]) => {
        if (!mounted) return
        setClients(c)
        setBarbers(b)
        setServices(s)
      })
      .catch((err) => {
        console.error(err)
        if (mounted) setError('Erro ao carregar dados')
      })
      .finally(() => mounted && setLoading(false))

    return () => { mounted = false }
  }, [])

  // envio do formulário
  const [saving, setSaving] = useState(false)

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault()
    const payload = { clientId, barberId, serviceId, date, time, status }
    try {
      setSaving(true)
      const created = await api.createAppointment(payload)
      onSave(created)
    } catch (err) {
      console.error('Erro ao salvar agendamento', err)
      setError('Erro ao salvar agendamento')
    } finally {
      setSaving(false)
    }
  }

  if (loading) return <div>Carregando...</div>
  if (error) return <div className="text-red-600">{error}</div>

  return (
    <form className="space-y-4" onSubmit={handleSubmit}>
      <div>
        <label className="block text-sm font-medium">Cliente</label>
        <select
          value={clientId}
          onChange={(e) => setClientId(e.target.value ? Number(e.target.value) : '')}
          className="mt-1 w-full rounded border p-2 bg-white"
        >
          <option value="">Selecionar cliente</option>
          {clients.map((c) => (
            <option key={c.id} value={c.id}>{c.name}</option>
          ))}
        </select>
      </div>

      <div>
        <label className="block text-sm font-medium">Barbeiro</label>
        <select
          value={barberId}
          onChange={(e) => setBarberId(e.target.value ? Number(e.target.value) : '')}
          className="mt-1 w-full rounded border p-2 bg-white"
        >
          <option value="">Selecionar barbeiro</option>
          {barbers.map((b) => (
            <option key={b.id} value={b.id}>{b.name}</option>
          ))}
        </select>
      </div>

      <div>
        <label className="block text-sm font-medium">Serviço</label>
        <select
          value={serviceId}
          onChange={(e) => setServiceId(e.target.value ? Number(e.target.value) : '')}
          className="mt-1 w-full rounded border p-2 bg-white"
        >
          <option value="">Selecionar serviço</option>
          {services.map((s) => (
            <option key={s.id} value={s.id}>{s.name}</option>
          ))}
        </select>
      </div>

      <div className="flex gap-4 items-end">
        <div className="w-1/3">
          <label className="block text-sm font-medium">Horário</label>
          <input type="time" value={time} onChange={(e) => setTime(e.target.value)} className="mt-1 w-full rounded border p-2 bg-white" />
        </div>

        <div className="flex-1">
          <label className="block text-sm font-medium">Data</label>
          <input type="date" value={date} onChange={(e) => setDate(e.target.value)} className="mt-1 w-full rounded border p-2 bg-white" />
        </div>

        <div className="w-1/3">
          <label className="block text-sm font-medium">Status</label>
          <select value={status} onChange={(e) => setStatus(e.target.value as any)} className="mt-1 w-full rounded border p-2 bg-white">
            <option value="agendado">Agendado</option>
            <option value="concluido">Concluído</option>
          </select>
        </div>
      </div>

      <div className="flex justify-end gap-3 pt-2">
        <button type="button" onClick={onCancel} disabled={saving} className="px-4 py-2 rounded bg-white border">Cancelar</button>
        <button type="submit" disabled={saving} className="px-4 py-2 rounded bg-black text-white">{saving ? 'Salvando...' : 'Salvar'}</button>
      </div>
    </form>
  )
}
