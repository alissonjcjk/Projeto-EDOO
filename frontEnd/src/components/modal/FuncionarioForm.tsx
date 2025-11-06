import { useState } from 'react'
import { api } from '../../services/api'

interface Props {
  onCancel: () => void
  onSave: (created?: any) => void
}

export default function FuncionariosForm({ onCancel, onSave }: Props) {
  const [name, setName] = useState('')
  const [role, setRole] = useState('')
  const [startTime, setStartTime] = useState('')
  const [endTime, setEndTime] = useState('')
  const [salary, setSalary] = useState('0')
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState<string | null>(null)

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault()
    setSaving(true)
    setError(null)
    try {
      //ageitando barbeiro
      const created = await api.createBarber({ nome, role, startTime, endTime, salary: Number(salary) })
      onSave(created)
    } catch (err) {
      console.error(err)
      setError('Erro ao salvar funcionário')
    } finally {
      setSaving(false)
    }
  }

  return (
    <form className="space-y-4" onSubmit={handleSubmit}>
      {error && <div className="text-red-600">{error}</div>}
      <div>
        <label className="block text-sm font-medium">Nome</label>
        <input value={name} onChange={(e) => setName(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="Digite o nome do funcionário" />
      </div>

      <div>
        <label className="block text-sm font-medium">Função</label>
        <input value={role} onChange={(e) => setRole(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="Selecione uma função" />
      </div>

      <div className="flex gap-4">
        <div className="flex-1">
          <label className="block text-sm font-medium">Horário Início</label>
          <input value={startTime} onChange={(e) => setStartTime(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="--:--" />
        </div>
        <div className="flex-1">
          <label className="block text-sm font-medium">Horário Fim</label>
          <input value={endTime} onChange={(e) => setEndTime(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="--:--" />
        </div>
      </div>

      <div>
        <label className="block text-sm font-medium">Salário (R$)</label>
        <input value={salary} onChange={(e) => setSalary(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" />
      </div>

      <div className="flex justify-end gap-3 pt-2">
        <button type="button" onClick={onCancel} disabled={saving} className="px-4 py-2 rounded bg-white border">Cancelar</button>
        <button type="submit" disabled={saving} className="px-4 py-2 rounded bg-black text-white">{saving ? 'Salvando...' : 'Salvar'}</button>
      </div>
    </form>
  )
}
