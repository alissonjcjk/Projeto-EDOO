import { useState } from 'react';
import Modal from '../components/modal/Modal'
import AgendamentoForm from '../components/modal/AgendamentoForm'


interface Agendamento {
  id: number;
  cliente: string;
  servico: string;
  barbeiro: string;
  data: string;
  hora: string;
  status: 'confirmado' | 'pendente' | 'cancelado';
}

export default function AgendamentosPage() {
    
  const [open, setOpen] = useState(false)
  const [agendamentos, setAgendamentos] = useState<Agendamento[]>([
    {
      id: 1,
      cliente: 'João Silva',
      servico: 'Corte Social',
      barbeiro: 'Francisco',
      data: '15/07/2024',
      hora: '14:30',
      status: 'confirmado'
    },
    {
      id: 2,
      cliente: 'Maria Santos',
      servico: 'Barba',
      barbeiro: 'Roberto',
      data: '15/07/2024',
      hora: '16:00',
      status: 'pendente'
    },
    {
      id: 3,
      cliente: 'Pedro Costa',
      servico: 'Corte + Barba',
      barbeiro: 'Francisco',
      data: '16/07/2024',
      hora: '10:00',
      status: 'cancelado'
    }
  ]);

  const handleEditar = (id: number) => {
    console.log('Editar agendamento:', id);
    // Aqui integrará com o backend
  };

  const handleCancelar = (id: number) => {
    setAgendamentos(agendamentos.filter(agendamento => agendamento.id !== id));
    // Aqui integrará com o backend
  };

  const getStatusColor = (status: string) => {
    switch (status) {
      case 'confirmado':
        return 'bg-green-100 text-green-800';
      case 'pendente':
        return 'bg-yellow-100 text-yellow-800';
      case 'cancelado':
        return 'bg-red-100 text-red-800';
      default:
        return 'bg-gray-100 text-gray-800';
    }
  };

  return (
    <div className="p-6">
      <div className="mb-8">
        <h1 className="text-3xl font-semibold mb-2">Agendamentos</h1>
        <p className="text-xl text-gray-600">Gerencie todos os agendamentos da barbearia</p>
      </div>

      <div className="bg-white rounded-lg border border-gray-200 overflow-hidden">
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Cliente</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Serviço</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Barbeiro</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Data</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Hora</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Status</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {agendamentos.map((agendamento) => (
                <tr key={agendamento.id} className="hover:bg-gray-50 transition-colors">
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm font-medium text-gray-900">{agendamento.cliente}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{agendamento.servico}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{agendamento.barbeiro}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{agendamento.data}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{agendamento.hora}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <span className={`inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium ${getStatusColor(agendamento.status)}`}>
                      {agendamento.status.charAt(0).toUpperCase() + agendamento.status.slice(1)}
                    </span>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                    <button 
                      onClick={() => handleEditar(agendamento.id)}
                      className="text-blue-600 hover:text-blue-900 mr-4 font-semibold"
                    >
                      Editar
                    </button>
                    <button 
                      onClick={() => handleCancelar(agendamento.id)}
                      className="text-red-600 hover:text-red-900 font-semibold"
                    >
                      Cancelar
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>

        <div className="border-t border-gray-200 px-6 py-4 bg-gray-50">
          <button 
            onClick={() => setOpen(true)}
            className="bg-red-600 text-white px-6 py-2 rounded-lg hover:bg-red-700 transition duration-200 font-semibold"
            aria-label="Novo Agendamento"

          >
            + Novo Agendamento
          </button>
        </div>
      </div>
       <Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Agendamento">
			<AgendamentoForm onCancel={() => setOpen(false)} onSave={() => setOpen(false)} />
		</Modal>

		{/* conteúdo da página vai aqui */}

    </div>
  );
}